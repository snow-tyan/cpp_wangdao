#include <cmath>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Figure
{
public:
    virtual void display() const = 0;
    virtual double area() const = 0;

};

class Triangle
:public Figure
{
public:
    Triangle(double a, double b, double c)
    :_a(a),_b(b),_c(c)
    {
        cout<<"Triangle(double, double, double)"<<endl;
    }

    void display() const
    {
        cout<<"triangle's area = "<<area()<<endl;
    }

    double area() const
    {
        double p=(_a+_b+_c)/2;
        return sqrt(p*(p-_a)*(p-_b)*(p-_c));
    }

private:
    double _a,_b,_c;//三边长度
};

void display(Figure *figure)
{
    figure->display();
    figure->area();
}

int main()
{
    Triangle triangle(3,4,5);
    display(&triangle);

    return 0;
}