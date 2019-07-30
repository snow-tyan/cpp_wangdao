#include <iostream>
using std::cout;
using std::endl;

#define MULTI(x,y) ((x)*(y))

inline
int multi(int x, int y)
{
    return x*y;
}

int main()
{
    int a=3,b=4;
    cout<<MULTI(a+1,b+1)<<endl;
    cout<<multi(a+1,b+1)<<endl;
    return 0;
}