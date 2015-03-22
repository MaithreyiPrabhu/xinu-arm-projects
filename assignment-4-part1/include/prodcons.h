/*
 * @file hello.h
 *
 * $Id: hello.h 2126 2014-02-05 07:23:04Z svn $
 */
/* Embedded Xinu, Copyright (C) 2008.  All rights reserved. */


#ifndef _PRODCONS_H_
#define _PRODCONS_H_

#include <stdio.h>
#include <stddef.h>
#include <future.h>

/*Global varible for producer consumer*/
extern int n;
//extern semaphore c ;
//extern semaphore p ;

/*function Prototype*/
void future_cons(future* fut);
void future_prod(future* fut);

#endif                          /* _PRODCONS_H_ */
