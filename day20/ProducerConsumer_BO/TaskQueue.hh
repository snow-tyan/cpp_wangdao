#pragma once
#include "MutexLock.hh"
#include "Condition.hh"
#include <queue>
using std::queue;

namespace PC_BO
{

class TaskQueue
{
public:
    TaskQueue(size_t size);

    bool empty() const;
    bool full() const;

    void push(int elem);
    int pop();

private:
    size_t _queSize;
    queue<int> _que;
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
};


}//end of namespace PC_BO