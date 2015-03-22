/**
 *  * @file future.h
 *  *
**/
#ifndef _FUTURE_H_
#define _FUTURE_H_

#include <queue.h>

/* Future state definitions */
#define FFREE 0x01 /**< this future is free */
#define FUSED 0x02 /**< this future is used */
#define CONSUMER_WAITING 0x03 /**< consumer is waiting for this future> **/
#define PRODUCED 0x04 /**< producer has produced the value> **/

/* type definition of "future" */
typedef unsigned int future;

/**
 *  * Semaphore table entry
 *   */
struct futent                   /* future table entry      */
{
    char state;                 /**< the state SFREE or SUSED */
    int* value;                  /**< value of this future */
    tid_typ tid;              /**< requires queue.h.        */
    int future_flags
};

extern struct futent futtab[];

/* isbadfuture - check validity of reqested future id and state */
#define isbadfuture(s) ((s >= NSEM) || (SFREE == futtab[s].state))

/* Future function prototypes */

/* This is for creating a future, 
 * this will allocate an entry from future table */
future* future_alloc(int future_flags); 

/* This is for deleting a future, this will free 
 * the entry used from future table */
syscall future_free(future*);

/* This will give the value of produced otherwise 
 * move the calling thread to waiting queue */
syscall future_get(future*, int*);

/* This will produce the value for the future 
 * and inform the thread waiting on this future if there's any */
syscall future_set(future*, int*);

#endif
