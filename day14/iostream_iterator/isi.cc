#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
using std::cout;
using std::endl;
using std::istream_iterator;
using std::vector;

int main()
{
    istream_iterator<int> isi(std::cin);
    vector<int> ivec(isi, istream_iterator<int>());
    std::copy(isi, istream_iterator<int>(), ivec.begin());

    for (auto &elem : ivec)
    {
        cout << elem << " ";
    }
    cout << endl;

    return 0;
}