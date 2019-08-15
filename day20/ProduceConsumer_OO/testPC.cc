#include "Producer.hh"
#include "Consumer.hh"
#include "TaskQueue.hh"
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;
using namespace PC_OO;

int main()
{
    cout << "i am main thread, PC_OO start" << endl;

    TaskQueue task(10);
    unique_ptr<Thread> producer(new Producer(task));
    unique_ptr<Thread> consumer(new Consumer(task));

    producer->start();
    consumer->start();

    producer->join();
    consumer->join();

    cout << "i am main thread, PC_OO finish" << endl;
    return 0;
}
