#include "line.h"
using namespace pimpl;

void test0()
{
    line sline(1, 2, 3, 4);
    sline.printLine();
}

int main()
{
    test0();
    // test1();
    return 0;
}