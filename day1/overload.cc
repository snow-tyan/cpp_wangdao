#include <iostream>
using namespace std;
extern "C"
{
int add(int x, int y)
{
    return x+y;
}
}
int main()
{
    add(3,4);

    return 0;
}

