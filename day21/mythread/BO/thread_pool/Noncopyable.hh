#pragma once

namespace myThread
{

class Noncopyable
{
public:
    Noncopyable() {}
    ~Noncopyable() {}

    //显示出现拷贝构造的话，必须显示给出默认构造
    Noncopyable(const Noncopyable &rhs) = delete;
    Noncopyable operator=(const Noncopyable &rhs) = delete;
};

} //end of namespace myThread