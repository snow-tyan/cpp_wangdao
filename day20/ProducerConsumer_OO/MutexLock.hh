#pragma once
#include "Noncopyable.hh"
#include <pthread.h>

namespace PC_OO
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

//RAII 技术体现，用生命周期管理互斥锁
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

} //end of namespace PC_OO