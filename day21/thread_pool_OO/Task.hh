#pragma once

namespace ThreadPool_OO
{

class Task
{
public:
    virtual void process() = 0;
    virtual ~Task() {}
};

}//end of namespace Thread_Pool_OO