#include "Consumer.hh"
#include "TaskQueue.hh"
#include <unistd.h>//sleep
#include <iostream>
using std::cout;
using std::endl;

namespace PC_OO
{
Consumer::Consumer(TaskQueue &taskQueue)
:_taskQueue(taskQueue)
{}

void Consumer::run()
{
    int cnt = 10;
    while (cnt--)
    {
        int num = _taskQueue.pop();
        cout << ">>> consumer thread, get num = " << num << endl;
        ::sleep(2);
    }
}

}//end of namespace PC_OO