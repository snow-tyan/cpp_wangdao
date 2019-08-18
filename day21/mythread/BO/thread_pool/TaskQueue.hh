#pragma once
#include "MutexLock.hh"
#include "Condition.hh"
#include <queue>
#include <functional>
using std::queue;

namespace myThread
{
using ElemType = std::function<void()>;

class TaskQueue
{
public:
    TaskQueue(size_t queSize);

    void push(ElemType);
    ElemType pop();

    bool full() const;
    bool empty() const;
    void wakeup();

private:
    size_t _queSize;
    queue<ElemType> _que;
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
    bool _wakeupFlag;
};

} //end of namespace myThread