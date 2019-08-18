#pragma once

namespace myThread
{

class Task
{
public:
    virtual void process() = 0;
    virtual ~Task(){}
};

}//end of namespace myThread