#include <iostream>
using std::cout;
using std::endl;

int main()
{
    const int number=100;
    // int *pint=&number//error
    // const int *pint=&number;//ok
    int *pint=const_cast<int*>(&number);//const->非const

    int value=200;
    const int *pValue=&value;//ok
    return 0;
}