#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define N 10

int cnt;
pthread_mutex_t lock;

void *
incr(void *arg)
{
    for (int i = 0; i < 1000000; i++)
    {
        // __sync_fetch_and_add(&cnt, 1); // Use atomic operation to increment cnt
        pthread_mutex_lock(&lock);
        cnt++;
        pthread_mutex_unlock(&lock); // Unlock the mutex after incrementing
    }
    return NULL;
}

int main()
{
    pthread_t pthread[N];
    pthread_mutex_init(&lock, NULL);
    for (int i = 0; i < N; i++)
    {
        pthread_create(&pthread[i], NULL, incr, NULL);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(pthread[i], NULL); // Wait for the pong thread to finish
    }
    printf("cnt = %d\n", cnt);
    return 0;
}