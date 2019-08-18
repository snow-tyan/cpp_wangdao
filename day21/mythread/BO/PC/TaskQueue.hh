#pragma once
#include "MutexLock.hh"
#include "Condition.hh"
#include <queue>
using std::queue;

namespace myThread
{
using ElemType = int;

class TaskQueue
{
public:
    TaskQueue(size_t queSize);

    void push(ElemType);
    ElemType pop();

    bool full() const;
    bool empty() const;

private:
    size_t _queSize;
    queue<ElemType> _que;
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
};

} //end of namespace myThread