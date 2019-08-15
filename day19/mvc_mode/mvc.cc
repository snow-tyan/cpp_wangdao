#include <iostream>
#include <string>
#include <memory>
#include <map>
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::unique_ptr;

class Student
{
public:
    Student(size_t id = 0, const string &name = string())
        : _id(id), _name(name)
    {
        cout << "Student(size_t, const string &)" << endl;
    }

    ~Student() { cout << "~Student()" << endl; }

    size_t getId() const { return _id; }
    string getName() const { return _name; }

private:
    size_t _id;
    string _name;
};

class View
{
public:
    View(Student *pstu = nullptr)
        : _pstu(pstu)
    {
        cout << "View(Student *)" << endl;
    }
    ~View() { cout << "~View()" << endl; }

    void reset(Student *pstu)
    {
        _pstu=pstu;
    }

    virtual void show()
    {
        cout << "id:" << _pstu->getId() << "  "
             << "name:" << _pstu->getName() << endl;
    }

private:
    Student *_pstu;
};

class Controller
{
public:
    void attach(const Student &stu)
    {
        //const对象只能掉用const成员函数
        _mapStudent.insert(std::make_pair(stu.getId(),stu));
    }

    void attach(Student &&stu)
    {
        _mapStudent[stu.getId()]=std::move(stu);
    }

    void detach(size_t id)
    {
        _mapStudent.erase(id);//返回移除的元素数
    }

    void show(View *view)
    {
        for(auto it = _mapStudent.begin();it!=_mapStudent.end();++it)
        {
            view->reset(&it->second);
            view->show();
        }
    }

private:
    map<size_t, Student> _mapStudent;
};

int main()
{
    Controller ctrl;
    ctrl.attach(Student(100,"xiongda"));
    Student stu;
    Student stu2(99,"xionger");
    ctrl.attach(stu);
    ctrl.attach(stu2);

    unique_ptr<View> view(new View());
    ctrl.show(view.get());

    return 0;
}
