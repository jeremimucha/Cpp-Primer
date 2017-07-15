// ex 14.42.cpp
/* Using library function objects and adaptors, define an expression to
(a) Count the number of values that are greater than 1024
(b) Find the first string that is not equal to  pooh
(c) Multiply all values by 2
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <functional>
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::greater;
using std::equal_to;
using std::multiplies;
using std::bind;
using std::placeholders::_1;


template<typename Iter>
void print_container(Iter b, Iter e);


int main()
{
// (a) Count the number of values that are greater than 1024
    vector<int> vi{1234, 11, 42, 0, 5432, 2347, 987, 55, 1478, 11111,22222,5555};
    std::size_t gt1024 = std::count_if(vi.cbegin(), vi.cend(),
                bind(greater<int>(), _1, 1024));
    cout << "(a) Count the number of values that are greater than 1024:";
    cout << "\nvector: ";
    print_container(vi.cbegin(), vi.cend());
    cout << "\nCount of numbers greater 1024: " << gt1024 << endl;

// (b) Find the first string that is not equal to  pooh
    vector<string> vs{"pooh", "pooh", "fooh", "pooh", "pooh", "notpooh, pooh"};
    vector<string>::const_iterator notpooh =
        std::find_if_not(vs.cbegin(), vs.cend(),
            bind(equal_to<string>(), _1, "pooh"));
    cout << "(b) Find the first string that is not equal to  pooh:";
    cout << "\nvector: ";
    print_container(vs.cbegin(), vs.cend());
    cout << "\nfirst element not equal to pooh: " << *notpooh << endl;
// (c) Multiply all values by 2
    vector<int> vodd{1,3,5,7,9,11,13,15,17,19};
    cout << "(c) Multiply all values by 2:";
    cout << "\noriginal vector:";
    print_container(vodd.cbegin(), vodd.cend());
    std::transform(vodd.begin(), vodd.end(), vodd.begin(),
            bind(multiplies<int>(), _1, 2));
    cout << "\nall values * 2: ";
    print_container(vodd.cbegin(), vodd.cend());
}


template<typename Iter>
void print_container(Iter b, Iter e)
{
    while( b != e ){
        cout << *b;
        if( ++b != e )
            cout << ", ";
    }
}
