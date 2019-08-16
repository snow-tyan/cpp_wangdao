#pragma once
#include "MutexLock.hh"
#include "Condition.hh"
#include <functional>
#include <queue>
using std::queue;

namespace ThreadPool_OO
{

class TaskQueue
{
public:
    using ElemType = std::function<void()>;
    TaskQueue(size_t size);

    bool empty() const;
    bool full() const;

    void push(ElemType elem);
    ElemType pop();
    void wakeup();//解决程序执行过快造成线程卡死退不出的问题

private:
    size_t _queSize;
    queue<ElemType> _que;
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
    bool _wakeupFlag;
};

}//end of namespace ThreadPool_OO