#include <stdio.h>
#include <pthread.h>

#include <stdlib.h>

pthread_mutex_t lock;
pthread_cond_t cond_b;
pthread_cond_t cond_c;
int bcp = 0;
int ccp = 0;
void *f1(void *arg)
{
    pthread_mutex_lock(&lock);
    while (bcp == 0)
    {
        pthread_cond_wait(&cond_b, &lock); // 与while搭配使用
    }
    printf("B\n");
    ccp = 1;
    pthread_cond_signal(&cond_c);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *f2(void *arg)
{
    printf("A\n");
    bcp = 1;
    pthread_mutex_lock(&lock);
    pthread_cond_signal(&cond_b); // 但是如果这个时候线程1还没被创建，这个信号没有用，等到1真正被创建就会被阻塞了
    pthread_mutex_unlock(&lock);

    pthread_mutex_lock(&lock);

    while (ccp == 0)
    {
        pthread_cond_wait(&cond_c, &lock);
    }
    printf("C\n");
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main()
{
    // init();
    pthread_t t1, t2;
    pthread_create(&t1, NULL, f1, NULL);
    pthread_create(&t2, NULL, f2, NULL); // 传参同时启动子程序
    pthread_join(t1, NULL);
    pthread_join(t2, NULL); // 获取返回值确保这两个进程都结束再继续运行下面的代码
}