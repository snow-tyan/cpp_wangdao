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

    unique_ptr<Thread> producer(new Thread(
        std::bind(&Producer::produce, Producer(), std::ref(task))
        , "生产者 1号")); //本对象可以用类名加()表示
    unique_ptr<Thread> consumer(new Thread(
        std::bind(&Consumer::consume, Consumer(), std::ref(task))
        , "消费者 2号"));

    producer->start();
    consumer->start();
    producer->join();
    consumer->join();

    cout << "main thread" << endl;
    return 0;
}
