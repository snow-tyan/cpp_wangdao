#pragma once
#include "Noncopyable.hh"
#include <pthread.h>

namespace ThreadPool_BO
{

class MutexLock
    : public Noncopyable //禁止复制
{
public:
    MutexLock();
    ~MutexLock();

    void lock();
    void unlock();

    pthread_mutex_t *getMutexPtr() { return &_mutex; }

private:
    pthread_mutex_t _mutex;
};

class MutexLockGuard
{
public:
    MutexLockGuard(MutexLock &mutex)
        : _mutex(mutex)
    {
        _mutex.lock();
    }

    ~MutexLockGuard() { _mutex.unlock(); }

private:
    MutexLock &_mutex;
};

} //end of namespace ThreadPool_BO