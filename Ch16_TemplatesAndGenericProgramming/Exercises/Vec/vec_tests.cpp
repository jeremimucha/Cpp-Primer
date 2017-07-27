#include <iostream>
#include <string>
#include <algorithm>
#include "vec.h"
using std::cout;
using std::endl;
using std::string;


template class Vec<int>;


int main()
{
    Vec<int> vi{1,2,3,4,5,6,7};
    Vec<string> vs{"one", "two", "three", "four"};
    cout << "vi: ";
    std::for_each(vi.cbegin(), vi.cend(), [](int i){std::cout << i << ", ";});
    cout << endl;
    cout << "vs: ";
    for( const string& s : vs){
        cout << s << ", ";
    }

    cout << "\nTesting emplace_back:\n";
    vs.emplace_back(4, 'A');
    vs.emplace_back(3, 'B');
    cout << "After vs.emplace_back(4, 'A') and vs.emplace_back(4, 'B')\n";
    for( const string& s : vs)
        cout << s << ", ";
}
