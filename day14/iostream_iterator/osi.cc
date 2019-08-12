#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;
using std::vector;
using std::ostream_iterator;

int main()
{
    vector<int> ivec={1,2,3,4,5};

    // ostream_iterator<int> osi(cout, ", ");
    std::ostream_iterator<int> osi(cout);

    std::copy(ivec.begin(),ivec.end(),osi);
    cout<<endl;

    return 0;
}