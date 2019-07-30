#include <iostream>
using std::cout;
using std::endl;
#define MAXSIZE 10
class Stack
{
public:
    Stack() : _top(0) { cout << "Stack()" << endl; }
    ~Stack() { cout << "~Stack()" << endl; }

    void push(int); //入栈
    void pop();     //弹栈
    int top();      //返回栈顶元素
    bool empty();   //栈空
    bool full();    //栈满

private:
    int _top;               //栈顶指针
    int _data[MAXSIZE + 1]; //栈大小，_data[0]不存储元素，_top==0--》栈空
};

void Stack::push(int value)
{
    if (!full())
    {
        cout << "push " << value << " to Stack" << endl;
        _top++;
        _data[_top] = value;
    }
    else
    {
        cout << "push error:Stack is full" << endl;
        exit(-1);
    }
}

void Stack::pop()
{
    if (!empty())
    {
        cout << "pop" << endl;
        _top--;
    }
    else
    {
        cout << "pop error:Stack is empty" << endl;
        exit(-1);
    }
}

int Stack::top()
{
    if (!empty())
    {
        return _data[_top];
    }
    else
    {
        cout << "top error:Stack is empty" << endl;
        exit(-1);
    }
}

bool Stack::empty()
{
    return (_top != 0) ? false : true;
}

bool Stack::full()
{
    return (_top != MAXSIZE) ? false : true;
}

int main()
{
    Stack stack;
    stack.push(10);
    cout << "top=" << stack.top() << endl;
    stack.push(12);
    stack.push(14);

    cout << "top=" << stack.top() << endl;
    stack.pop();
    cout << "top=" << stack.top() << endl;
    stack.pop();
    stack.pop();
    stack.pop();

    return 0;
}