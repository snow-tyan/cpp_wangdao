#include "ThreadPool.hh"
#include <unistd.h>
#include <iostream>
using std::cout;
using std::endl;

namespace ThreadPool_BO
{

ThreadPool::ThreadPool(size_t threadNum, size_t queSize)
    : _threadNum(threadNum), _queSize(queSize), _taskque(queSize), _isExit(false)
{
    _threads.reserve(threadNum);
    //reserve只是开辟空间，并没有创建对象，此时size==0
    //若要使用下标运算符，需确定下标合法
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
    //创建线程对象
    for (size_t idx = 0; idx != _threadNum; ++idx)
    {
        unique_ptr<Thread> thread(new Thread(
            std::bind(&ThreadPool::threadFunc, this), std::to_string(idx + 1)));
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
    if (!_isExit)
    {
        #if 1
        while (!_taskque.empty())//任务队列不空时
        {
            // ::sleep(1);
            // ::usleep(100000);
            ::usleep(1);
        }
        #endif

        //当任务执行的速度太快，在将_isExit设置为true之前，
        //每一个子线程都已经取任务，此时发现_taskque之中没有任务了
        //所有都会阻塞在_notEmpty的条件变量之上，从而卡死
        _isExit = true;
        _taskque.wakeup();//解决方法，唤醒所有子线程

        //回收每个子线程
        for (auto &thread : _threads)
        {
            thread->join();
        }
    }
}

void ThreadPool::addTask(Task &&task)
{
    _taskque.push(std::move(task));
}

//每一个线程都要完成的任务
void ThreadPool::threadFunc()
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

ThreadPool::Task ThreadPool::getTask()
{
    return _taskque.pop();
}

} //end of namespace ThreadPool_BO