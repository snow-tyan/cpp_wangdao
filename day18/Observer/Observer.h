//Observer.h
#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Observer
{
public:
	//void update(Subject*);//拉模式, 观察者主动接收信息
	//void update(Message);//推模式, 观察者被动接收信息
	virtual void update() = 0;
	virtual ~Observer() { cout << "~Observer()" << endl; }
};

class Baby
	: public Observer
{
public:
	Baby(const string & name)
		: _name(name)
	{}

	void update()
	{
		::srand(::clock());
		int number = ::rand() % 100;
		if (number < 70) {
			cout << "Baby " << _name << " is sleeping sweetly!" << endl;
		}
		else {
			cout << "Baby " << _name << " is starting crying loudly!" << endl;
		}
	}

private:
	string _name;
};

class Nurse
	: public Observer
{
public:
	Nurse(const string & name)
		: _name(name)
	{}

	void update()
	{
		::srand(::clock());
		int number = ::rand() % 100;
		if (number < 70) {
			cout << "Nurse " << _name << " is awake, and is ready to open the door!" << endl;
		}
		else {
			cout << "Nurse " << _name << " is sleeping sweetly!" << endl;
		}
	}
private:
	string _name;
};