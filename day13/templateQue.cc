#include <iostream>
using std::cout;
using std::endl;

template <typename T, int kSize = 10>
class Que
{
public:
    Que();
    ~Que();

    bool full() const;
    bool empty() const;
    void push(const T &t);
    void pop();
    T &front() const;
    T &back() const;

private:
    int _front;
    int _back;
    T *_data;
};

template <typename T, int kSize>
Que<T, kSize>::Que()
    : _front(0), _back(0), _data(new T[kSize]())
{
}

template <typename T, int kSize>
Que<T, kSize>::~Que()
{
    if (_data)
    {
        delete[] _data;
    }
}

template <typename T, int kSize>
bool Que<T, kSize>::full() const
{
    return (_back + 1) % kSize == _front;
}

template <typename T, int kSize>
bool Que<T, kSize>::empty() const
{
    return _back == _front;
}

template <typename T, int kSize>
void Que<T, kSize>::push(const T &t)
{
    if (!full())
    {
        _data[_back++] = t;
        _back %= kSize;
    }
    else
    {
        cout << "illegal options! Que is full." << endl;
    }
}

template <typename T, int kSize>
void Que<T, kSize>::pop()
{
    if (!empty())
    {
        ++_front;
        _front %= kSize;
    }
    else
    {
        cout << "illegal options! Que is empty." << endl;
    }
}

template <typename T, int kSize>
T &Que<T, kSize>::front() const
{
    return _data[_front];
}

template <typename T, int kSize>
T &Que<T, kSize>::back() const
{
    return _data[_back - 1];
}

void test0()
{
    Que<int> que;
    cout << "Que is empty? " << que.empty() << endl;
    cout << "Now push 9 8 7 6 5 4 3 2 1" << endl;
    for (int i = 9; i != 0; --i)
    {
        que.push(i);
    }
    cout << "Que is full? " << que.full() << endl;
    cout << "Now pop 5 datas" << endl;
    for (int i = 0; i != 5; ++i)
    {
        que.pop();
    }
    cout << "que's front = " << que.front() << " back = " << que.back() << endl;
    cout << "Que is empty? " << que.empty() << endl;
    cout << "Now push 6 datas" << endl;
    for (int i = 0; i != 6; ++i)
    {
        que.push(i + 10);
    }
    cout << "Que is full? " << que.full() << endl;
    cout << "pop all" << endl;
    for (int i = 0; i != 9; ++i)
    {
        que.pop();
    }
    cout << "Que is empty? " << que.empty() << endl;
}

int main()
{
    test0();

    return 0;
}