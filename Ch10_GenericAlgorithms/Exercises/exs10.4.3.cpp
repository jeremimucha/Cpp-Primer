// exs10.4.3.cpp - exercise section 10.4.3
/*Exercise 10.34: Use  reverse_iterator s to print a  vector in reverse order.
Exercise 10.35: Now print the elements in reverse order using ordinary
iterators.
Exercise 10.36: Use  find to find the last element in a  list of  int s with
value 0.
Exercise 10.37: Given a  vector that has ten elements, copy the elements
from positions 3 through 7 in reverse order to a  list .*/
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
using std::vector;
using std::list;
using std::cout;


template<typename Iter>
void print_container(Iter begin, Iter end)
{
    while( begin != end ){
        cout << *begin;
        if( ++begin != end )
            cout << ", ";
    }
}


int main()
{
    vector<int> vi{0,1,2,3,4,5,6,7,8,42,0,11,2,3,4,5};
    cout << "vi: ";
    print_container(vi.cbegin(), vi.cend());

// ex 10.34
    cout << "\n\nex 10.34:";
    cout << "\nvi in reverse using reverse_iterators: ";
    print_container(vi.crbegin(), vi.crend());
    
// ex 10.35
    cout << "\n\nex 10.35:";
    cout << "\nvi in reverse using ordinary iterators: ";
    for(auto it=vi.cend(); it!=vi.cbegin();){
        cout << *--it;
        if( it != vi.cbegin() )
            cout << ", ";
    }

// ex 10.36
    cout << "\n\nex 10.36:";
    vector<int>::const_reverse_iterator zero = std::find(vi.crbegin(), vi.crend(), 0);
    // .base() is the underlying iterator - it points to the element one after
    // the element pointed to by the reverse_iterator
    cout << "\nThe last element = 0:\n\tindex: " << ( (zero.base()-1) - vi.cbegin())
         << "\n\tvalue: " << *zero;

// ex 10.37
    cout << "\n\nex 10.37:";
    vector<int> v10{0,1,2,3,4,5,6,7,8,9};
    cout << "v10: ";
    print_container(v10.cbegin(), v10.cend());
    list<int> li;
    std::copy(v10.crbegin()+2, v10.crend()-2, std::back_inserter(li));
    cout << "\nli after copying values from index 3 through 7 in reverse.\n"
         << "li: ";
    print_container(li.cbegin(), li.cend());
}
