#include <iostream>
#include <cstdio>
using namespace std;

size_t minHp(size_t hp1, size_t hp2, size_t hp3, size_t hp4, size_t hp5)
{
    return min(min(min(min(hp1,hp2),hp3),hp4),hp5);
}

int main()
{
    size_t a;
    a=minHp(4,6,1,2,9);
    cout<<a<<endl;
    return 0;
}