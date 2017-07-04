// ex10.42.cpp
/*Reimplement the program that eliminated duplicate
words that we wrote in § 10.2.3 (p. 383) to use a  list instead of a  vector .*/
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
using std::cout;
using std::string;
using std::list;


template<typename Iter>
void print_container(Iter begin, Iter end);


int main()
{
    list<string> ls{"list", "with", "some", "duplicate", "unsorted", "duplicate",
            "some", "list", "words", "with", "words"};
    cout << "ls: ";
    print_container(ls.cbegin(), ls.cend());
    ls.sort();
    cout << "\nafter sort: ";
    print_container(ls.cbegin(), ls.cend());
    ls.unique();
    cout << "\nafter unique: ";
    print_container(ls.cbegin(), ls.cend());

}


template<typename Iter>
void print_container(Iter begin, Iter end)
{
    while( begin != end ){
        cout << *begin;
        if( ++begin != end )
            cout << ", ";
    }
}
