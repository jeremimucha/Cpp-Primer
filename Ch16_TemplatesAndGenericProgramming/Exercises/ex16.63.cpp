/* Exercise 16.63: Define a function template to count the number of
occurrences of a given value in a  vector . Test your program by passing it a
vector of  double s, a  vector of  int s, and a  vector of  string s. */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::placeholders::_1;

template<typename T>
std::size_t countof(const std::vector<T>& v, const T& t);


int main()
{
    vector<int> vi{1,2,42,3,4,42,5,6,42,7,8,42};
    std::size_t cvi = countof(vi, 42);
    cout << "countof(vi, 42) = " <<cvi <<endl;
}


template<typename T>
std::size_t countof(const std::vector<T>& v, const T& t)
{
    return std::count(v.cbegin(), v.cend(), t);
    // return std::count_if(v.cbegin(), v.cend(),
    //     std::bind(std::equal_to<T>(), _1, t));
}
