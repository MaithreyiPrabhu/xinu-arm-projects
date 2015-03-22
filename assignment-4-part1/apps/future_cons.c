 /**
  * @file consumer.c
  * @provides a greeting msg
  *
  * $Id: consumer.c 2009 2004-2-02 udayanga/lahiru $
  */
 /* Embedded Xinu, Copyright (C) 2008.  All rights reserved. */

 #include <prodcons.h>


 void future_cons(future* fut)
 {
     //Code to consume values of global variable 'n' until the value
     //of n is less than or equal to count
     //print consumed value e.g. consumed : 8
     int* value;
     if(future_get(fut,value) == SYSERR)
     {
     	fprintf(stderr,"Error consuming the value\n\r");
	return;
     }
     printf("Consumed the value : %d\n\r",*value);
 }
