#include <func.h>
#include <iostream>
using std::cout;
using std::endl;
#define NUM 20000000
void cleanup(void *p);

class MutexLock
{
public:
    int getVal() { return _val; }
    int plusOne() { return _val += 1; }
    void lock() { pthread_mutex_lock(&_mutex); }
    void unlock() { pthread_mutex_unlock(&_mutex); }
    void init() { pthread_mutex_init(&_mutex, nullptr); }

private:
    int _val = 0;
    pthread_mutex_t _mutex;
};

class Condition
{
public:
    void lock() { pthread_mutex_lock(&_mutex); }
    void unlock() { pthread_mutex_unlock(&_mutex); }
    void init()
    {
        pthread_mutex_init(&_mutex, nullptr);
        pthread_cond_init(&_cond, nullptr);
    }
    void wait() { pthread_cond_wait(&_cond, &_mutex); }
    void notify() { pthread_cond_signal(&_cond); }
    void notifyall() { pthread_cond_broadcast(&_cond); }
    void clean_push_pop()
    {
        pthread_cleanup_push(cleanup, &_mutex);
        pthread_cond_wait(&_cond, &_mutex);
        cout << "I am child thread, I am waiting" << endl;
        pthread_cleanup_pop(1);
    }

private:
    pthread_mutex_t _mutex;
    pthread_cond_t _cond;
};

void cleanup(void *p)
{
    Condition *pArg = (Condition *)p;
    pArg->unlock();
    cout << "clean up ok" << endl;
}

void *add(void *p)
{
    MutexLock *pArg = (MutexLock *)p;
    for (int i = 0; i < NUM; i++)
    {
        pArg->lock();
        pArg->plusOne();
        pArg->unlock();
    }
    pthread_exit(nullptr);
}

void *threadFunc(void *p)
{
    Condition *pArg = (Condition *)p;
    pArg->lock();
    pArg->clean_push_pop();
    cout << "I am child thread, I wake up" << endl;
    pthread_exit(nullptr);
}

int main()
{
    MutexLock mutex;
    mutex.init();
    pthread_t pthid1, pthid2;
    pthread_create(&pthid1, nullptr, add, &mutex);
    pthread_create(&pthid2, nullptr, add, &mutex);
    pthread_join(pthid1, nullptr);
    pthread_join(pthid2, nullptr);
    cout << "val=" << mutex.getVal() << endl
         << "-------------------------" << endl;

    Condition condi;
    condi.init();
    pthread_t pthid3, pthid4;
    pthread_create(&pthid3, nullptr, threadFunc, &condi);
    pthread_create(&pthid4, nullptr, threadFunc, &condi);
    pthread_cancel(pthid3);
    pthread_cancel(pthid4);
    pthread_join(pthid3, nullptr);
    pthread_join(pthid4, nullptr);
    cout << "I am main thread" << endl;

    return 0;
}