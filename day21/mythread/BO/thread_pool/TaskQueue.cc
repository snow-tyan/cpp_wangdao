#include "TaskQueue.hh"

namespace myThread
{

TaskQueue::TaskQueue(size_t queSize)
    : _queSize(queSize), _mutex(), _notFull(_mutex), _notEmpty(_mutex), _wakeupFlag(true) {}

//生产者线程
void TaskQueue::push(ElemType elem)
{
    MutexLockGuard autoLock(_mutex); //放产品操作，加解锁
    while (full())
    {
        _notFull.wait();
    }
    _que.push(elem);
    _notEmpty.notify();
}

//消费者线程
ElemType TaskQueue::pop()
{
    MutexLockGuard autoLock(_mutex); //取产品操作，加解锁
    while (_wakeupFlag && empty())
    {
        _notEmpty.wait();
    }

    if (_wakeupFlag)
    {
        ElemType elem = _que.front(); //线程栈空间
        _que.pop();
        _notFull.notify();
        return elem;
    }
    else
    {
        return nullptr;
    }
}

bool TaskQueue::full() const
{
    return _que.size() == _queSize;
}
bool TaskQueue::empty() const
{
    return _que.size() == 0;
}

void TaskQueue::wakeup()
{
    _wakeupFlag = false;
    _notEmpty.notifyall();
}

} //end of namespace myThread