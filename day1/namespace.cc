#include <iostream>
using std::cout;
using std::endl;

namespace wd
{
int show(); //函数的声明

//命名空间的嵌套使用
namespace snow
{
int display()
{
    cout << "snow::dispay()" << endl;
    return 0;
}
} //end of namespace snow

} //end of namespace wd

namespace tls
{
int print()
{
    cout << "tls::print()" << endl;
    wd::show();
}

} //end of namespace tls

namespace wd
{
int display()
{
    cout << "wd::display()" << endl;
    tls::print();
}

int show()
{
    cout << "wd::show()" << endl;
}

} //end of namespace wd

int main(void)
{
    wd::display();
    cout << "I am here" << endl;
    wd::snow::display();

    return 0;
}