#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void segfault_sigaction(int signal, siginfo_t *si, void *arg)
{
    printf("Caught segfault at address %p\n", si->si_addr);
    printf("Successful count value %d \n",*((int*)arg));
    exit(0);
}

int main(void)
{
    char *foo = (char*)malloc(sizeof(char));
    int char_size = sizeof(char);
    struct sigaction sa;
    int* count;
    memset(&sa, 0, sizeof(sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = segfault_sigaction;
    sa.sa_flags   = SA_SIGINFO;

    sigaction(SIGSEGV, &sa, (void*)count);
    *count = 0;
    /* Cause a seg fault */ 
    while(1)
    { 
	*foo = *(foo - 1); 
	(*count)++;
    }
    return 0;
}
