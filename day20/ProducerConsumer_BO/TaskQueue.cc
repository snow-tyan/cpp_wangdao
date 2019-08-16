#include "TaskQueue.hh"

namespace PC_BO
{

TaskQueue::TaskQueue(size_t size)
:_queSize(size)
,_mutex()
,_notFull(_mutex)
,_notEmpty(_mutex)
{}

bool TaskQueue::empty() const
{
    return _que.size()==0;
}

bool TaskQueue::full() const
{
    return _que.size()==_queSize;
}

//运行在生产者线程上
void TaskQueue::push(int elem)
{
    MutexLockGuard autoLock(_mutex);
    while(full())//使用while，防止虚假唤醒
    {
        _notFull.wait();
    }

    _que.push(elem);
    _notEmpty.notify();
}

//运行在消费者线程上
int TaskQueue::pop()
{
    MutexLockGuard autoLock(_mutex);
    while(empty())
    {
        _notEmpty.wait();
    }
    int elem = _que.front();
    _que.pop();
    
    _notFull.notify();
    return elem;
}

}//end of PC_BO