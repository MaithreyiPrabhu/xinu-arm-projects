#include <stdio.h>     /* printf, perror */
#include <stdlib.h>    /* exit */
#include <unistd.h>
int main(void)
{
    printf("Address of function printf which is from stdio  =%p\n",&printf);
    printf("Address of function read   which is from unistd =%p\n",&read);
    return EXIT_SUCCESS;
}
