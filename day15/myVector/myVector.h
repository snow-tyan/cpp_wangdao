#pragma once
#include <iostream>
#include <memory>
#include <algorithm>
using std::cout;
using std::endl;

template <typename T>
class myVector
{
public:
    using value_type = T;
    using iterator = T *;
    // using const_iterator = const T *;
    using reference = T &;
    using size_type = size_t;    

    //构造函数
    myVector() : _start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {}//无参构造
    myVector(size_type n, const T &value) { fill_initialize(n,value); }
    explicit myVector(size_type n) { fill_initialize(n, T()); }

    //复制控制函数
    // myVector(const myVector &rhs);

    //析构函数
    ~myVector();


    iterator begin() { return _start; }
    iterator end() { return _finish; }
    size_type size() { return _finish - _start; }
    size_type capacity() { return _end_of_storage - _start; }
    bool empty() { return begin() == end(); }
    reference front()   {   return *begin();    }
    reference back()    { return *(end()-1);    }
    reference operator[](size_t idx) const { return _start[idx]; }

    void push_back(const reference);
    void pop_back();
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);
    // void resize( size_type newSize, const reference value);

private:
    void reallocate(); //重新分配内存
    void fill_initialize(size_type n, const T &value)
    {
        _start = _alloc.allocate(n);               //开n个空间
        std::uninitialized_fill_n(_start, n, value); //填充并初始化
        _finish = _start + n;
        _end_of_storage = _finish;
    }

private:
    static std::allocator<T> _alloc;
    iterator _start;          //首指针
    iterator _finish;         //尾后元素指针
    iterator _end_of_storage; //实际空间尾后指针
};

template <typename T>
std::allocator<T> myVector<T>::_alloc;

template <typename T>
myVector<T>::~myVector()
{
    if (_start)
    {
        while (_finish != _start)
        {
            _alloc.destroy(--_finish);
        }
        _alloc.deallocate(_start, capacity());
    }
}

template <typename T>
void myVector<T>::push_back(const reference value)
{
    if (size() == capacity())
    {
        reallocate();
    }
    //在分配的内存上构造对象
    _alloc.construct(_finish++, value);
}

template <typename T>
void myVector<T>::reallocate()
{
    size_type cap = capacity(); //回收空间用
    size_type newCap = 2 * cap > 0 ? 2 * cap : 1;
    T *pNewCap = _alloc.allocate(newCap); //开辟新空间

    if (_start)
    {
        //把放在原空间的值 copy 到新空间
        //std::copy不能拷贝到没有对象的空间
        std::uninitialized_copy(_start, _finish, pNewCap);

        //销毁对象
        while (_finish != _start)
        {
            //destory一次只能销毁一个对象
            _alloc.destroy(--_finish); //这里只能用finish前移，因为start还要用来回收空间
        }
        //回收旧空间
        _alloc.deallocate(_start, cap);
    }

    //更新三个指针
    _start = pNewCap;
    _finish = _start + cap;
    _end_of_storage = _start + newCap;
}

template <typename T>
void myVector<T>::pop_back()
{
    if (_start)
    {
        _alloc.destroy(--_finish);
    }
}

template <typename T>
typename myVector<T>::iterator myVector<T>::erase(iterator pos)
{
    if(pos!=end()-1)
    {
        std::copy(pos+1,_finish,pos);//后面的元素向前移
    }
    _alloc.destroy(--_finish);
    return pos; //返回删除元素之后的迭代器
}

template <typename T>
typename myVector<T>::iterator myVector<T>::erase(iterator first, iterator last)
{
    //后面的元素向前移
    iterator newFinish = std::copy(last, _finish, first);
    while (_finish != newFinish)
    {
        _alloc.destroy(--_finish);
    }
    return first; //返回删除元素之后的迭代器
}