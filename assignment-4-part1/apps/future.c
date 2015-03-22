/**
 *  * @file wait.c
 *   * @provides wait.
 *    *
 *     * $Id: wait.c 2020 2009-08-13 17:50:08Z mschul $
 *      */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <thread.h>
#include <interrupt.h>
#include <future.h>

static future futmalloc();

future* future_alloc(int future_flags)
{
    	register future* fut;
	irqmask im;
    	im = disable();             /* disable interrupts    */
    
    	fut = malloc(sizeof(future));
 
    	*fut  = futmalloc();           /* request new future entry */
    	if (*fut != SYSERR)    /* safety check          */
    	{
		restore(im);            /* restore interrupts    */
        	return fut;             /* return the future   */
    	}
	
	restore(im);
    	return SYSERR;	
}



syscall future_free(future* fut)
{
	register struct futent *entry;
	irqmask im;
	im = disable();    /* disable interrupts */
	if (isbadfuture(*fut))
    	{
        	restore(im);
        	return SYSERR;
    	}
	entry = &futtab[*fut];
	if(entry->state == CONSUMER_WAITING)  /* if someone is waiting moving it to ready queue */
	{
		ready(entry->tid,RESCHED_YES);
	}	
	entry->state = FFREE;
	restore(im);
	return OK;
}

syscall future_get(future* fut, int* value)
{
	register struct futent *entry;
	register struct thrent *thrptr;
	irqmask im;
	im = disable();
	if(isbadfuture(*fut))
	{
		restore(im);
		return SYSERR;
	}
	entry = &futtab[*fut];
	if(entry->state == PRODUCED) /* value is already produced */
	{
		*value = *(entry->value); /* readig the value to value pointer */
		restore(im);
		return OK;	
	}
	else if(entry->state == FUSED)  /* value is not yet produced */
	{
		entry->state = CONSUMER_WAITING;    /* going to waiting queue until value get produced */
		thrptr = &thrtab[thrcurrent];
		thrptr->state = THRWAIT;
		entry->tid = thrcurrent;
		resched();   		/* rescheduling, no need to restore interrupt, it will be done by resched()*/
		im = disable();
		*value = *(entry->value);       /* reading the value after it get produced, this line get executed only when value is available */
	}
	restore(im);
	return OK;
}
	
syscall future_set(future* fut, int* value)
{
	register struct futent *entry;
	irqmask im;
	im = disable();
	if(isbadfuture(*fut))
	{
		restore(im);
		return OK;	
	}
	entry = &futtab[*fut];
	// storing the value for the future
	entry->value = value;		/* storing the value inside future */
	if(entry->state == FUSED)	
	{
		entry->state = PRODUCED;	/* nobody is waiting at this point */
	}	
	else if(entry->state == CONSUMER_WAITING)	/* someone is waiting for the value */
	{
		entry->state = PRODUCED;
		ready(entry->tid,RESCHED_YES);		/* releasing the waiting thread */ 
	} 
	restore(im);
	return OK;	

}


/* This will give the first available entry in future table*/
future futmalloc()
{
	int fut = 0;                /* future to return */
    	static int nextfut = 0;

    	for (fut = 0; fut < NFUT; fut++)
    	{
        	nextfut = (nextfut + 1) % NFUT;
        	if (SFREE == futtab[nextfut].state)
        	{
            		futtab[nextfut].state = FUSED;
            		return nextfut; 
        	}
    	}
    	return SYSERR;
}
