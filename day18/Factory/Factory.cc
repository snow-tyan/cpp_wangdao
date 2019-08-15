#include <cmath>
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

//开闭原则：对修改关闭，对扩展开放

class Figure
{
public:
	virtual void display() const = 0;
	virtual double area() const = 0;

	virtual ~Figure() { cout << "~Figure()" << endl; }
};

class Rectangle
	:public Figure
{
public:
	Rectangle(double length, double width)
		:_length(length)
		, _width(width)
	{
		cout << "Rectangle(double, double)" << endl;
	}

	void display() const
	{
		cout << "This rectangle's area = ";
	}

	double area() const
	{
		return _length * _width;
	}

private:
	double _length;
	double _width;
};

class Circle
	: public Figure
{
public:
	Circle(double radius)
		: _radius(radius)
	{
		cout << "Circle()" << endl;
	}

	void display() const
	{
		cout << "This circle's area = ";
	}

	double area() const
	{
		return 3.14159 * _radius * _radius;
	}

private:
	double _radius;
};

class Triangle
	: public Figure
{
public:
	Triangle(double a, double b, double c)
		: _a(a)
		, _b(b)
		, _c(c)
	{
		cout << "Triangle()" << endl;
	}

	void display() const
	{
		cout << "This triangle's area = ";
	}

	double area() const
	{
		double p = (_a + _b + _c) / 2;
		return sqrt(p * (p - _a) * (p - _b) * (p - _c));
	}

private:
	double _a;
	double _b;
	double _c;
};

//Factory 模式
//前提条件:
//	 1. 针对于复杂对象
//	 2. 批量创建对象
//
//对于简单对象，不适合使用Factory 模式

class Factory
{
public:
	virtual Figure * create() = 0;
	virtual ~Factory() { cout << "~Factory()" << endl; }
};

class RectangleFactory
	:public Factory
{
public:
	Figure * create()
	{
		//...
		return new Rectangle(3, 4);
	}
};

class CircleFactory
	:public Factory
{
public:
	Figure * create()
	{
		//...
		return new Circle(2);
	}
};

class TriangleFactory
	:public Factory
{
public:
	Figure * create()
	{
		//...
		return new Triangle(3, 4, 5);
	}
};

void showArea(Figure * fig)
{
    fig->display();
	cout << fig->area() << endl;
}

int main()
{
	unique_ptr<Factory> rectangleFactory(new RectangleFactory());
	unique_ptr<Figure> rectangle(rectangleFactory->create());

	unique_ptr<Factory> circleFactory(new CircleFactory());
	unique_ptr<Figure> circle(circleFactory->create());

	unique_ptr<Factory> triangleFactory(new TriangleFactory());
	unique_ptr<Figure> triangle(triangleFactory->create());

	showArea(rectangle.get());
	showArea(circle.get());
	showArea(triangle.get());

	return 0;
}