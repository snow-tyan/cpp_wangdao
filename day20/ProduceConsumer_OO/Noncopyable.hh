#pragma once

namespace PC_OO
{

class Noncopyable
{
public:
    Noncopyable() {}
    ~Noncopyable() {}

    Noncopyable(const Noncopyable &) = delete;
    Noncopyable operator=(const Noncopyable &) = delete;
};

} //end of namespace PC_OO