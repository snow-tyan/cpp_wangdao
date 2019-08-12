#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using std::cout;
using std::endl;
using std::ostream_iterator;
using std::vector;

void test0()
{
    vector<int> ivec = {1, 9, 9, 5, 1, 2, 1, 9};
    std::copy(ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));

    cout << endl
         << "After erase-remove" << endl;
    ivec.erase(std::remove_if(ivec.begin(), ivec.end(), [](int number) { return number > 3; }), ivec.end());

    std::copy(ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

void test1()
{
    vector<int> ivec = {1, 9, 9, 5, 1, 2, 1, 9};
    std::copy(ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    int sz = 3;
    cout << endl
         << "After erase-remove" << endl;
    ivec.erase(std::remove_if(ivec.begin(), ivec.end(), [sz](int number) -> bool { return number > sz; }), ivec.end());
   
   
    int sz = 3;
    auto f = [sz](int number) -> bool { return number > sz; };


    std::copy(ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

int main()
{
    // test0();
    test1();

    return 0;
}