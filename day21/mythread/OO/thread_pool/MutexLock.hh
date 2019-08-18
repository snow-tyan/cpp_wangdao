#pragma once
#include "Noncopyable.hh"
#include <cstdio>
#include <pthread.h>

namespace myThread
{

class MutexLock
    :public Noncopyable
{
public:
    MutexLock()
    {
        if(pthread_mutex_init(&_mutex,nullptr))
        {
            perror("pthread_mutex_init");
        }
    }
    ~MutexLock()
    {
        if(pthread_mutex_destroy(&_mutex))
        {
            perror("pthread_mutex_destory");
        }
    }

    void lock()
    {
        if(pthread_mutex_lock(&_mutex))
        {
            perror("pthread_mutex_lock");
        }
    }
    void unlock()
    {
        if(pthread_mutex_unlock(&_mutex))
        {
            perror("pthread_mutex_unlock");
        }
    }

    pthread_mutex_t *getMutexPtr() { return &_mutex; }

private:
    pthread_mutex_t _mutex;
};

class MutexLockGuard
{
public:
    MutexLockGuard(MutexLock &mutex)
    :_mutex(mutex)
    {
        _mutex.lock();
    }

    ~MutexLockGuard()
    {
        _mutex.unlock();
    }

private:
    MutexLock &_mutex;
};

}//end of namespace myThread