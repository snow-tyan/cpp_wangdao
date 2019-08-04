#include <iostream>
using namespace std;

class Base
{
    static double _db;
};

int main()
{
    cout<<sizeof(Base)<<endl;
    return 0;
}