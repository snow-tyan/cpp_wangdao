//Subject.cc
#include "Subject.h"
#include "Observer.h"
#include <algorithm>

void Ring::isPressed()
{
	if (!_isAlarming)
	{
		_isAlarming = true;
		notify();
	}

	_isAlarming = false;
}

void Ring::attach(Observer * obj)
{
	auto it = std::find(_obList.begin(), _obList.end(), obj);
	if (it == _obList.end())
	{
		_obList.push_back(obj);
	}
}

void Ring::detach(Observer * obj)
{
	auto it = std::find(_obList.begin(), _obList.end(), obj);
	if (it != _obList.end()) {
		_obList.erase(it);
	}
}

void Ring::notify()
{
	for (auto & obj : _obList) 
	{
		obj->update();
	}
}

void Guest::knock(Ring & ring)
{
	cout << ">>> Guest " << _name << " is knocking at the door!" << endl;
	ring.isPressed();
}