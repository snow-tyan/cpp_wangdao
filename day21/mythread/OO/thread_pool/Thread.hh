#pragma once
#include <pthread.h>
#include "Noncopyable.hh"
#include <iostream>
#include <string>
using std::string;

namespace myThread
{
extern __thread const char * threadName;

class Thread
    : public Noncopyable
{
public:
    //基类必须有默认构造
    Thread(const string &name = string())
        : _pthid(0), _isRunning(false), _name(name)
    {
        // std::cout << "Thread()" << std::endl;
    }

    void start();
    void join();

    virtual ~Thread();
    virtual void run() = 0;

private:    
    //threadFunc必须是只带一个void *类型的参数，返回void *类型的函数
    //设为static，以消除this指针的影响
    static void *threadFunc(void *arg);

private:
    pthread_t _pthid;
    bool _isRunning;
    string _name;
};

} //end of namespace myThread