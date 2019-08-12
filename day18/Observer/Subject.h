//Subject.h
#pragma once
#include <iostream>
#include <list>
#include <string>
using std::cout;
using std::endl;
using std::list;
using std::string;

class Observer;

class Subject
{
public:
	virtual void attach(Observer * obj) = 0;
	virtual void detach(Observer * obj) = 0;
	virtual void notify() = 0;

	virtual ~Subject() { cout << "~Subject()" << endl; }
};

class Ring
	:public Subject
{
public:
	Ring():_isAlarming(false){}
	
	void isPressed();

	virtual void attach(Observer * obj);
	virtual void detach(Observer * obj);
	virtual void notify();

private:
	list<Observer*> _obList;
	bool _isAlarming;
};

class Guest
{
public:
	Guest(const string &name):_name(name){}

	void knock(Ring &ring);

private:
	string _name;
};