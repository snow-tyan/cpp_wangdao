#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

//类模板
template <typename T, int kSize=10>
class Stack
{
public:
    Stack();
    ~Stack();

    bool full() const;
    bool empty() const;
    void push(const T &t);//入栈
    void pop();//出栈
    T & top() const;//返回栈顶元素

private:
    int _top;//栈顶指针
    T * _data;
};

template <typename T, int kSize>
Stack<T, kSize>::Stack()
    : _top(-1), _data(new T[kSize]())
{}

template <typename T, int kSize>
Stack<T, kSize>::~Stack()
{
    if(_data)
    {
        delete []_data;
    }
}

template <typename T, int kSize>
bool Stack<T, kSize>::full() const
{
    return _top==kSize-1;
}

template <typename T, int kSize>
bool Stack<T, kSize>::empty() const
{
    return _top==-1;
}

template <typename T, int kSize>
void Stack<T, kSize>::push(const T &t)
{
    if(!full())
    {
        _data[++_top]=t;
    }
    else
    {
        cout<<"illegal options! Stack is full."<<endl;
    }    
}

template <typename T, int kSize>
void Stack<T, kSize>::pop()
{
    if(!empty())
    {
        --_top;
    }
    else
    {
        cout<<"illegal options! Stack is empty."<<endl;
    }   
}

template <typename T, int kSize>
T & Stack<T, kSize>::top() const
{
    return _data[_top];
}

void test0()
{
    Stack<int> stack;
    cout<<"Stack is empty? "<<stack.empty()<<endl;
    for(int i=10;i!=0;--i)
    {
        stack.push(i);
    }
    cout<<"Stack is full? "<<stack.full()<<endl;
    stack.push(0);
    for(int j=0;j!=10;++j)
    {
        cout << "top = " << stack.top() << " --> pop" << endl;
        stack.pop();
    }
    cout<<"Stack is empty? "<<stack.empty()<<endl;
    stack.pop();
}

int main()
{
    test0();

    return 0;
}