#include "myVector.h"
#include <vector>
using std::vector;

template <typename Container>
void showContainer(Container &c)
{
    typename Container::iterator cit = c.begin();
    while (cit != c.end())
    {
        cout << *cit << " ";
        ++cit;
    }
    cout << endl;
}

template <typename Container>
void showCapacity(Container &c)
{
    cout << "size = " << c.size() << endl;
    cout << "capacity = " << c.capacity() << endl;
}

//test0 is myVector
void test0()
{
    myVector<int> myvec;
    for(int i=0;i!=6;++i)
    {
        myvec.push_back(i);
        showCapacity(myvec);
        showContainer(myvec);
        cout<<endl;
    }

    myvec.pop_back();
    myvec.pop_back();
    myvec.pop_back();
    showCapacity(myvec);
    showContainer(myvec);
}

//test1 is stl_vector
void test1()
{
    vector<int> ivec;
    for(int i=0;i!=6;++i)
    {
        ivec.push_back(i);
        showCapacity(ivec);
        showContainer(ivec);
        cout<<endl;
    }

    ivec.pop_back();
    ivec.pop_back();
    ivec.pop_back();
    showCapacity(ivec);
    showContainer(ivec);
}
#if 1
void test2()
{
    myVector<int> myvec;
    cout << "myvec is empty? "<<myvec.empty()<<endl;
    cout<<"-------------------------------"<<endl;
    myVector<int> myvec2(10,7);
    showContainer(myvec2);
    cout<<"-------------------------------"<<endl;
    myVector<int> myvec3(10);
    showContainer(myvec3);
    cout<<"-------------------------------"<<endl;
    myVector<int> myvec4;
    for(int i=1;i!=11;++i)
        myvec4.push_back(i);
    showContainer(myvec4);    
    cout<<"erase (2,5)"<<endl;
    myvec4.erase(myvec4.begin() + 2, myvec4.begin() + 5);
    showContainer(myvec4);
    cout<<"-------------------------------"<<endl;

}
#endif

int main()
{
    // test0();
    // test1();
    test2();
    // test3();

    return 0;
}