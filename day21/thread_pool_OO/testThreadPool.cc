#include "ThreadPool.hh"
#include "Task.hh"

#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
using std::cout;
using std::endl;
using namespace ThreadPool_OO;

class  Mytask
:public Task
{
public:
    void process() override
    {
        // ::srand(::clock());
        static int num = 1;
        int cnt = 2;
        while (cnt--)
        {
            // int num = ::rand() % 100;
            cout << ">> sub thread " << pthread_self() << " put num = " << num++ << endl;
            // ::sleep(1);
        }
    }
};

int main()
{
	ThreadPool threadpool(4, 10);//4个线程，任务队列大小10
	threadpool.start();

	unique_ptr<Task> task(new Mytask());
    
	int cnt = 20;
	while(cnt--) {
		threadpool.addTask(task.get());
		cout << ">> main thread : cnt = " << cnt << endl;
	}

	threadpool.stop();

	return 0;
}