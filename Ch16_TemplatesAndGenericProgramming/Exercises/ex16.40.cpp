/* Exercise 16.40: Is the following function legal? If not, why not? If it is
legal, what, if any, are the restrictions on the argument type(s) that can be
passed, and what is the return type?
Code:
template <typename It>
auto fcn3(It beg, It end) -> decltype(*beg + 0)
{
// process the range
return *beg; // return a copy of an element from the range
} */
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;


template<typename It>
auto fcn(It beg, It end) -> decltype(*beg + 0)
{
    return *beg;
}


int main()
{
    vector<int> vi{1,2,3,4};
    int i = fcn(vi.begin(), vi.end());
    cout << "i = " << i << endl;
    i += 42;
    cout << "i += 42 = " << i << endl;
    cout << "vi[0] = " << vi[0] << endl;    
}
