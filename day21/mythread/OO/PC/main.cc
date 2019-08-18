#include "Producer.hh"
#include "Consumer.hh"
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;
using namespace myThread;

int main()
{
    TaskQueue task(10); //queSize = 10
    unique_ptr<Thread> producer(new Producer(task, "生产者 1号"));
    unique_ptr<Thread> consumer(new Consumer(task, "消费者 2号"));

    producer->start();
    consumer->start();
    producer->join();
    consumer->join();

    cout << "main thread" << endl;
    return 0;
}
