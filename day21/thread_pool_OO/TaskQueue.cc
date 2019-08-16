#include "TaskQueue.hh"
#include "Task.hh"

namespace ThreadPool_OO
{

TaskQueue::TaskQueue(size_t size)
:_queSize(size)
,_mutex()
,_notFull(_mutex)
,_notEmpty(_mutex)
,_wakeupFlag(true)
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
void TaskQueue::push(ElemType elem)
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
TaskQueue::ElemType TaskQueue::pop()
{
    MutexLockGuard autoLock(_mutex);
    while (_wakeupFlag && empty())
    {
        _notEmpty.wait();
    }
    if (_wakeupFlag)
    {
        ElemType elem = _que.front();
        _que.pop();

        _notFull.notify();
        return elem;
    }
    else
    {
        return nullptr;
    }
}

void TaskQueue::wakeup()
{
    _wakeupFlag=false;
    _notEmpty.notifyall();
}

}//end of namespace ThreadPool_OO
