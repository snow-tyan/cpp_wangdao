//test.cc
#include "Subject.h"
#include "Observer.h"
#include <memory>
using std::unique_ptr;

int main()
{
	unique_ptr<Observer> baby1(new Baby("baby1"));
	unique_ptr<Observer> baby2(new Baby("baby2"));
	unique_ptr<Observer> nurse1(new Nurse("nurse1"));
	unique_ptr<Observer> nurse2(new Nurse("nurse2"));

	Ring ring;
	ring.attach(baby1.get());
	ring.attach(baby2.get());
	ring.attach(nurse1.get());
	ring.attach(nurse2.get());

	Guest guest("guest");

	guest.knock(ring);
	ring.detach(nurse2.get());
	cout << ">> " << endl;
	guest.knock(ring);

	return 0;
}