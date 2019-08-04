#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

template <typename T>
T add(const T &a, const T &b)
{
    return a + b;
}

int main()
{
    string a("Hello");
    string b = "World";
    cout << "add(1,2) = " << add(1, 2) << endl
         << "add(1.0+2.0) = " << add(1.0, 2.0) << endl
         << "add(\"Hello\",\"World\") = " << add(a, b) << endl;
    return 0;
}