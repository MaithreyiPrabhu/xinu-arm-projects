Project members
================
uswickra - Udayanga Wickramasinghe
lginnali - Lahiru Ginnaliya Gamathige 


Instructions to Run
====================


a) Extract the tarball and compile the source code from compile directory.

	This will create the binary in compile directory.

b) Start Xinu and log into Xinu shell - xsh

c) Type :  xsh$ prodcons 

d)example usage :  xsh$ prodcons 

Output : 
Consumed the value : 10
Produced the value : 10 
Consumed the value : 10
Produced the value : 10 
Consumed the value : 10
Produced the value : 10


Following is the test code in xsh_prodcons.c which uses the futures.

    f1 = future_alloc(0);
    f2 = future_alloc(0);
    f3 = future_alloc(0);

    resume( create(future_cons, 1024, 20, "fcons1", 1, f1) );
    resume( create(future_prod, 1024, 20, "fprod1", 1, f1) );
    resume( create(future_cons, 1024, 20, "fcons2", 1, f2) );
    resume( create(future_prod, 1024, 20, "fprod2", 1, f2) );
    resume( create(future_cons, 1024, 20, "fcons3", 1, f3) );
    resume( create(future_prod, 1024, 20, "fprod3", 1, f3) );


e) help :  xsh$ prodcons --help

Output : 

Usage: prodcons 

Description:
        Creates a producer and a consumer and Displays produced and consumed values on console 
	This will make sure that produced values are consumed properly and we
	are running thread threads and producer is producing a contant value

        --help  display this help and exit


Files in the implementation
===========================


/include/future.h -  This contains the future function declarations
/apps/future.c  -  This contains the future implementation methods
/apps/future_prod.c - Customized producer code to use futures
/apps/future_cons.c - Customized consumer code to use futures
/include/prodcons.h - Function definitions for producer/consumer
/shell/xsh_prodcons.c - Producer consumer invocation code with future initialization.

Collaboration
==============

We both discussed the design and implementation

Since this is a relatively small project ,We covered the assignment independently and finalized the code in a single repository and using that repo
to do the submission.

