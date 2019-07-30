#pragma once

#include <iostream>

namespace pimpl
{

class line
{
    class lineImpl;

public:
    line(int, int, int, int);
    ~line();

    void printLine() const;

private:
    lineImpl *_pImpl;
};

} // namespace pimpl