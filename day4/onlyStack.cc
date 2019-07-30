#include <cstring>
#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;

//需求: 一个类只能创建出栈对象, 不能创建堆对象
//解决方案: 只需要将operator new放在私有区域
class Student
{
public:
    Student(int id, const char *name)
        : _id(id), _name(new char[strlen(name) + 1]())
    {
        cout << "Student(int, const char *)" << endl;
        strcpy(_name, name);
    }

    ~Student()
    {
        cout << "~Student()" << endl;
        if (_name)
        {
            delete[] _name;
            _name = nullptr;
        }
    }

    void print() const
    {
        cout << "id=" << _id << endl
             << "name=" << _name << endl;
    }

private:
    void *operator new(size_t sz);
    void operator delete(void *p);

private:
    int _id;
    char *_name;
};

void *Student::operator new(size_t sz)
{
    cout << "void * operator new(size_t)" << endl;
    void *ret = malloc(sz);
    return ret;
}

void Student::operator delete(void *p)
{
    cout << "void operator delete(void *)" << endl;
    free(p);
}

int main()
{
    Student s1(1001,"cortna");
    s1.print();

    // Student *s2=new Student(1002,"lusy");//error
    // s2->print();
    // delete s2;

    return 0;
}