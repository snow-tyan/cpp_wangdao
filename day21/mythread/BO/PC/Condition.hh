#pragma once
#include "MutexLock.hh"

namespace myThread
{

class Condition
    :public Noncopyable
{
public:
    Condition(MutexLock &mutex)
    :_mutex(mutex)
    {
        if(pthread_cond_init(&_cond,nullptr))
        {
            perror("pthread_cond_init");
        }
    }
    ~Condition()
    {
        if(pthread_cond_destroy(&_cond))
        {
            perror("pthread_cond_destory");
        }
    }

    void wait()
    {
        if(pthread_cond_wait(&_cond,_mutex.getMutexPtr()))
        {
            perror("pthread_cond_wait");
        }
    }
    void notify()
    {
        if(pthread_cond_signal(&_cond))
        {
            perror("pthread_cond_signal");
        }
    }
    void notifyall()
    {
        if(pthread_cond_broadcast(&_cond))
        {
            perror("pthread_cond_broadcast");
        }
    }

private:
    MutexLock &_mutex;
    pthread_cond_t _cond;
};

}//end of namespace myThread
