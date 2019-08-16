#pragma once

namespace ThreadPool_BO
{

class Noncopyable
{
public:
    Noncopyable() {}
    ~Noncopyable() {}

    Noncopyable(const Noncopyable &) = delete;
    Noncopyable operator=(const Noncopyable &) = delete;
};

} //end of namespace ThreadPool_BO