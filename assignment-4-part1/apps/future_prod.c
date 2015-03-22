 /**
  * @file producer.c
  * @provides a greeting msg
  *
  * $Id: producer.c 2009 2004-2-02 udayanga/lahiru $
  */
 /* Embedded Xinu, Copyright (C) 2008.  All rights reserved. */

 #include <prodcons.h>

 void future_prod(future* fut)
 {
      //Code to produce values less than equal to count,
      //prodcued value should get assigned to global variable 'n'.
      //print produced value e.g. produced : 8
        int *value = (int*)malloc(sizeof(int));
	*value = 10;
	future_set(fut,value);
        printf("Produced the value : %d \r\n", *value);
 }
