#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *p_fib(void *arg)
{

    int *p = arg;
    if (*p < 2)
    {
        int *res = malloc(sizeof(int));
        *res = 1;
        return res;
    }
    int *res = malloc(sizeof(int));
    pthread_t pthread1;
    pthread_t pthread2;
    int arg1 = *p - 1;
    int arg2 = *p - 2;
    pthread_create(&pthread1, NULL, p_fib, (void *)&arg1);
    pthread_create(&pthread2, NULL, p_fib, (void *)&arg2);
    int *result1;
    int *result2;
    pthread_join(pthread1, (void *)&result1);
    pthread_join(pthread2, (void *)&result2);
    *res = *result1 + *result2;
    free(result1);
    free(result2);

    return res;
}

int main()
{
    pthread_t pthread; // Create a thread to run the pong function
    int arg = 4;
    pthread_create(&pthread, NULL, p_fib, (void *)&arg);
    int *result;
    pthread_join(pthread, (void *)&result); // Wait for the pong thread to finish
    printf("fib(%d) = %d\n", arg, *result);
    return 0;
}