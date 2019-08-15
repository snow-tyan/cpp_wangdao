#include "Producer.hh"
#include "TaskQueue.hh"
#include <unistd.h>//sleep
#include <ctime>
#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;

namespace PC_OO
{
Producer::Producer(TaskQueue &taskQueue)
    : _taskQueue(taskQueue)
{}

void Producer::run()
{
    ::srand(::clock());
    int cnt = 10;
    while (cnt--)
    {
        int num = ::rand() % 100;
        _taskQueue.push(num);
        cout << ">> produce thread, push num = " << num << endl;
        ::sleep(1);
    }
}

} //end of namespace PC_OO