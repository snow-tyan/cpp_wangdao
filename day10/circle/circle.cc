#include <iostream>
using std::cout;
using std::endl;
#define PI 3.14

class Circle
{
public:
    Circle()
        : _radius(0.0)
    {
        cout << "Circle()" << endl;
    }
    Circle(double radius)
        : _radius(radius)
    {
        cout << "Circle(double)" << endl;
    }

    ~Circle() { cout << "~Circle()" << endl; }

    double getArea() //获取圆的面积
    {
        return PI * _radius * _radius;
    }
    double getPerimeter() //获取圆的周长
    {
        return 2 * PI * _radius;
    }
    void show() //将圆的半径、周长、面积输出到屏幕
    {
        cout << "Circle's radius = " << _radius << endl
             << "Circle's perimeter = " << getPerimeter() << endl
             << "Circle's Area = " << getArea() << endl;
    }

private:
    double _radius; //圆的半径
};

class Cylinder
    : public Circle
{
public:
    Cylinder(double radius, double high)
        : Circle(radius), _high(high)
    {
        cout << "Cylinder(double, double)" << endl;
    }

    double getVolume() { return getArea() * _high; }
    void showVolume()
    {
        cout << "Cylinder's volume = " << getVolume() << endl;
    }

private:
    double _high; //圆柱体的高
};

void test0()
{
    Circle cir1;
    Circle cir2(1);

    cir1.show();
    cir2.show();
}

void test1()
{
    Cylinder cylin(5, 5);
    cylin.showVolume();
}

int main()
{
    // test0();
    test1();
    return 0;
}