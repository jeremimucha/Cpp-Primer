// ex10.24.cpp
/*Use  bind and  check_size to find the first element in a
vector of  int s that has a value greater than the length of a specified
string value.*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;
using std::bind;
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;


bool check_size(const string& s, string::size_type sz);


int main()
{
    vector<int> numbers{0,1,2,3,4,5,6,7,8,9,10,11};
    vector<int>::const_iterator it =
        std::find_if(numbers.cbegin(), numbers.cend(),
                     std::bind(check_size, "foobar", _1));
    cout << "element in the 'numbers' vector longer than 'foobar':\n"
         << "\tindex: " << it - numbers.cbegin()
         << "\n\tvalue: " << *it
         << endl;
}


bool check_size(const string& s, string::size_type sz)
{
    return s.size() < sz;
}
