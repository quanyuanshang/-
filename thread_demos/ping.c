#include <stdio.h>
#include <pthread.h>
void *pong(void *arg)
{
    printf("pong!\n");
    return NULL;
}

int main()
{
    pthread_t pthread; // Create a thread to run the pong function
    printf("ping!\n");
    pthread_create(&pthread, NULL, pong, NULL);
    pthread_join(pthread, NULL); // Wait for the pong thread to finish

    return 0;
}