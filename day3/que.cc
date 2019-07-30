#include <iostream>
using std::cout;
using std::endl;
#define MAXSIZE 5

class Que
{ //循环队列
public:
    Que() : _front(0), _back(0) { cout << "Que()" << endl; }
    ~Que() { cout << "~Que()" << endl; }

    void push(int); //入队
    void pop();     //出队
    int front();    //返回队首元素
    int back();     //返回队尾元素
    bool empty();   //队空
    bool full();    //队满

private:
    int _front;             //队首指针，指向队首元素前一个位置
    int _back;              //队尾指针，指向队尾元素
    int _data[MAXSIZE + 1]; //队大小，_data[0]不存元素
};

void Que::push(int value)
{
    if (!full()) //队不满，队尾指针后移
    {
        cout << "push " << value << " to Que" << endl;
        _back = (_back + 1) % MAXSIZE;
        _data[_back] = value;
    }
    else
    {
        cout << "push error:Que is full" << endl;
        exit(-1);
    }
}

void Que::pop()
{
    if (!empty())//队不空，队首元素出队
    {
        cout << "pop" << endl;
        _front = (_front + 1) % MAXSIZE;
    }
    else
    {
        cout << "pop error:Que is empty" << endl;
        exit(-1);
    }
}

int Que::front()
{
    if (!empty())
    {
        return _data[_front+1];
    }
    else
    {
        cout << "get front error:Que is empty" << endl;
        exit(-1);
    }
}

int Que::back()
{
    if (!empty())
    {
        return _data[_back];
    }
    else
    {
        cout << "get back error:Que is empty" << endl;
        exit(-1);
    }
}

bool Que::empty()
{
    return (_front!=_back) ? false : true;
}

bool Que::full()
{
    return ((_back + 1) % MAXSIZE != _front) ? false : true;
}

int main()
{
    Que que;
    que.push(10);
    que.pop();
    que.push(12);
    que.push(13);

    cout << "front=" << que.front() << endl
         << "back=" << que.back() << endl;
    
    que.push(14);
    que.pop();
    que.push(15);
    que.push(16);
    que.pop();
    que.push(17);

    cout << "front=" << que.front() << endl
         << "back=" << que.back() << endl;

    return 0;
}