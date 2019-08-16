#include "Producer.hh"
#include "Consumer.hh"
#include "TaskQueue.hh"
#include "Thread.hh"
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;
using namespace PC_BO;

int main()
{
    cout << "i am main thread, PC_BO start" << endl;
	TaskQueue taskque(10);
	
	unique_ptr<Thread> producer(new Thread(
		std::bind(&Producer::produce,Producer(), std::ref(taskque))			
	));

	unique_ptr<Thread> consumer(new Thread(
		std::bind(&Consumer::consume,Consumer(), std::ref(taskque))			
	));

    producer->start();
    consumer->start();

    producer->join();
    consumer->join();

    cout << "i am main thread, PC_BO finish" << endl;
    return 0;
}
