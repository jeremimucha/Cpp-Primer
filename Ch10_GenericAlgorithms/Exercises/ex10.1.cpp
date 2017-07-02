// ex10.1.cpp
/*The  algorithm header defines a function named  count that,
like  find , takes a pair of iterators and a value.  count returns a count of
how often that value appears. Read a sequence of  int s into a  vector and
print the  count of how many elements have a given value.*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using std::vector;
using std::cin;
using std::cout;
using std::endl;


int main()
{
    cout << "Enter some integers:\n";
    int i;
    vector<int> ints;
    while( cin >> i )
        ints.push_back(i);
    
    int count42 = std::count(ints.cbegin(), ints.cend(), 42);
    cout << "Entered values:\n";
    for(auto a : ints) cout << a << " ";
    cout << "\n";
    cout << "Number of values = 42: " << count42 << "\n";
    cout << "\nDone.\n";
    return 0;
}
