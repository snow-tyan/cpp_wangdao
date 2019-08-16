#pragma once
// #include "MutexLock.hh"
#include "Noncopyable.hh"
#include <pthread.h>

namespace ThreadPool_OO
{
//减小头文件的依赖关系，用前向声明
class MutexLock;

class Condition
    : public Noncopyable
{
public:
    Condition(MutexLock &mutex);
    ~Condition();

    void wait();
    void notify();
    void notifyall();

private:
    pthread_cond_t _cond;
    MutexLock &_mutex;
};

} //end of namespace ThreadPool_OO