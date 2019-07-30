#include <func.h>

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}Data_t,*pData_t;

void cleanup(void *p)
{
    pData_t pArg=(pData_t)p;
    pthread_mutex_unlock(&pArg->mutex);
    printf("clean up ok\n");
}

void *threadFunc(void *p)
{
    pData_t pArg=(pData_t)p;
    pthread_mutex_lock(&pArg->mutex);
    pthread_cleanup_push(cleanup,&pArg->mutex);
    pthread_cond_wait(&pArg->cond,&pArg->mutex);
    printf("I am child thread, I am waiting\n");
    pthread_cleanup_pop(1);
    printf("I am child thread, I wake up\n");
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    Data_t threadInfo;
    pthread_mutex_init(&threadInfo.mutex,NULL);
    pthread_cond_init(&threadInfo.cond,NULL);
    pthread_t pthid1, pthid2;
    pthread_create(&pthid1,NULL,threadFunc,&threadInfo);
    pthread_create(&pthid2,NULL,threadFunc,&threadInfo);
    int ret;
    ret=pthread_cancel(pthid1);
    THREAD_ERROR_CHECK(ret,"pthread_cancel");
    ret=pthread_cancel(pthid2);
    THREAD_ERROR_CHECK(ret,"pthread_cancel");
    ret=pthread_join(pthid1,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    ret=pthread_join(pthid2,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("I am main thread\n");
    return 0;
}
