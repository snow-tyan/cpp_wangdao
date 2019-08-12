#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using std::cout;
using std::endl;
using std::mem_fn;
using std::vector;

class Number
{
public:
	Number(int data)
	: _data(data)
	{}

	void display() const
	{	cout << _data << " ";}

	bool isEven() const
	{
		return (_data % 2 == 0);
	}

	bool isPrime() const
	{
		if(_data == 1 || _data == 0)	
			return false;
		for(int idx = 2; idx <= _data / 2; ++idx) {
			if(_data % idx == 0)
				return false;
		}
		return true;
	}

private:
	int _data;
};
 
int main(void)
{
	vector<Number> numbers;
	for(int idx = 0; idx != 30; ++idx) {
		numbers.emplace_back(idx);
	}

	std::for_each(numbers.begin(), numbers.end(),mem_fn(&Number::display));
	cout << endl;

	numbers.erase(std::remove_if(numbers.begin(), numbers.end(), mem_fn(&Number::isEven)),
			numbers.end());
 
	std::for_each(numbers.begin(), numbers.end(),mem_fn(&Number::display));
	cout << endl;

	numbers.erase(std::remove_if(numbers.begin(), numbers.end(), mem_fn(&Number::isPrime)),
			numbers.end());

	std::for_each(numbers.begin(), numbers.end(),mem_fn(&Number::display));
	cout << endl;
	return 0;
}
