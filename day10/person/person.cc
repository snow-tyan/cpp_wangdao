#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class person
{
public:
    person(string name, int age)
        : _name(name), _age(age)
    {
        cout << "person(string, int)" << endl;
    }

    ~person() { cout << "~person()" << endl; }

    string getName() { return _name; }
    int getAge() { return _age; }
    void display()
    {
        cout << "name = " << _name << endl
             << "age = " << _age << endl;
    }

private:
    string _name;
    int _age;
};

class employee
    : public person
{
public:
    employee(string name, int age, string department, double salary)
        : person(name, age), _department(department), _salary(salary)
    {
        cout << "employee(string, int, string, double)" << endl;
    }
    ~employee() { cout << "~employee()" << endl; }

    void display()
    {
        cout << "employee: " << endl;
        cout << "name = " << getName() << endl
             << "age = " << getAge() << endl
             << "department = " << _department << endl
             << "salary = " << _salary << endl;
    }

private:
    string _department;
    double _salary;
};

void test0()
{
    person p1("xiongda", 5);
    person p2("xiaoming", 13);

    p1.display();
    p2.display();
}

void test1()
{
    employee boy1("szy", 23, "China Construction Eighth Bureau", 7000);
    employee boy2("zst", 23, "DONT KNOW", 0);
    employee boy3("hzq", 23, "China Construction Eighth Bureau", 8000);
    boy1.display();
    boy2.display();
    boy3.display();
    boy1.person::display();
}

int main()
{
    // test0();
    test1();

    return 0;
}