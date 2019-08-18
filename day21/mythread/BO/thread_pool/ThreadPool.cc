#include "ThreadPool.hh"
#include <unistd.h>
#include <algorithm>

namespace myThread
{

ThreadPool::ThreadPool(size_t threadNum, size_t queSize)
    : _threadNum(threadNum), _queSize(queSize), _taskQue(queSize), _isExit(false)
{
    _threads.reserve(threadNum);
}

ThreadPool::~ThreadPool()
{
    if (!_isExit)
    {
        stop();
    }
}

void ThreadPool::start()
{
    //创建对象
    for (size_t idx = 0; idx != _threadNum; ++idx)
    {
        unique_ptr<Thread> thread(new Thread(
            std::bind(&ThreadPool::threadPoolFunc, this)
            , std::to_string(idx + 1)));
        _threads.push_back(std::move(thread)); //push_back底层使用的复制，
                                               //智能指针不能复制
    }
    //运行线程
    for (auto &thread : _threads)
    {
        thread->start();
    }
}

void ThreadPool::stop()
{
    while (!_taskQue.empty())
    {
        ::sleep(1);
    }

    _isExit = true;
    _taskQue.wakeup();
    //回收每个子线程
    for (auto &thread : _threads)
    {
        thread->join();
    }
}
void ThreadPool::addTask(Task &&task)
{
    _taskQue.push(std::move(task));
}

void ThreadPool::threadPoolFunc()
{
    while (!_isExit)
    {
        Task task = getTask();
        if (task)
        {
            task();
        }
    }
}
Task ThreadPool::getTask()
{
    return _taskQue.pop();
}

} //end of namespace myThread