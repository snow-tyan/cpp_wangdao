#pragma once

namespace thread_OO
{

class Noncopyable
{
public:
    Noncopyable() {}
    ~Noncopyable() {}

    Noncopyable(const Noncopyable &) = delete;
    Noncopyable operator=(const Noncopyable &) = delete;
};

} //end of namespace thread_OO