#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

class Computer
{
public:
	Computer(const char * brand, float price)
	: _brand(new char[strlen(brand)+ 1]())
	, _price(price)
	{
		strcpy(_brand, brand);
		cout << "Computer(const char*, float)" << endl;
	}

	void print();

	//系统提供的不满足需求
	//~Computer(){}

	~Computer()
	{//析构函数的作用是用来清理对象开辟的资源
        if (_brand)
        {
            delete[] _brand;
            cout << "delete" << endl;
        }
        cout<<"~Computer"<<endl;
    }

private:
	char * _brand;
	float _price;
};
 

inline void Computer::print()
{
	cout << "brand:" << _brand << endl
		 << "price:" << _price << endl;
}


Computer gPc("Xiaomi", 7500);

int test0(void)
{
	//自定义类类型
	cout << "sizeof(Computer) = " << sizeof(Computer) << endl;
	Computer pc("Thinkpad", 8888);
	cout <<  "pc = ";
	pc.print();

	// Computer pc2("ACER", 6666);
	// cout << "pc2 = ";
	// pc2.print();

	gPc.print();
 
	return 0;
}

int main(void)
{
    test0();
    static Computer pc3("Lenovo", 5555);
    pc3.print();

    Computer *pc4 = new Computer("MateBook", 7500);
    pc4->print();

    delete pc4;
	return 0;
}