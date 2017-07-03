// ex10.27.cpp
/*In addition to  unique (§ 10.2.3, p. 384), the library
defines function named  unique_copy that takes a third iterator denoting a
destination into which to copy the unique elements. Write a program that
uses  unique_copy to copy the unique elements from a  vector into an initially
empty  list .*/
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
using std::cout;
using std::endl;
using std::vector;
using std::list;


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
    vector<int> vi{1,1,1,2,2,2,3,3,3,4,4,42,42,42,11,11,11};
    cout << "vi: ";
    print_container(vi.cbegin(), vi.cend());
    list<int> li;
    std::unique_copy(vi.cbegin(), vi.cend(), std::back_inserter(li));
    cout << "\nunique_copy using back_inserter(li): ";
    print_container(li.cbegin(), li.cend());
    list<int> li2;
    std::unique_copy(vi.cbegin(), vi.cend(), std::back_insert_iterator<list<int>>(li2));
    cout << "\nunique_copy using back_insert_iterator<list<int>>(li2): ";
    print_container(li2.cbegin(), li2.cend());
    cout << "\n\nusing unique instead of unique_copy:\n";
    vector<int>::iterator vi_uend = std::unique(vi.begin(), vi.end());
    cout << "before erasing: ";
    print_container(vi.cbegin(), vi.cend());
    vi.erase(vi_uend, vi.cend());
    cout << "\nafter erase: ";
    print_container(vi.cbegin(), vi.cend());
}
