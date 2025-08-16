#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
int fib(int n)
{
    if (n < 2)
    {
        return 1;
    }
    return fib(n - 1) + fib(n - 2);
}

void *p_fib(void *arg)
{
    int *p = arg;
    int *res = malloc(sizeof(int));
    *res = fib(*p);

    return res;
}

int main()
{
    pthread_t pthread; // Create a thread to run the pong function
    int arg = 10;
    pthread_create(&pthread, NULL, p_fib, (void *)&arg);
    int *result;
    pthread_join(pthread, (void *)&result); // Wait for the pong thread to finish
    printf("fib(%d) = %d\n", arg, *result);
    return 0;
}