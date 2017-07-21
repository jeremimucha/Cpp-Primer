/* Exercise 16.4: Write a template that acts like the library  find algorithm.
The function will need two template type parameters, one to represent the
function’s iterator parameters and the other for the type of the value. Use
your function to find a given value in a  vector<int> and in a  list<string> .
*/
#include <iostream>
#include <vector>
#include <list>
#include <string>
using std::cout;
using std::endl;
using std::vector;
using std::list;
using std::string;


template<typename Iter, typename T>
Iter find(Iter b, Iter e, T value);


template<typename Iter>
void print_containter(Iter b, Iter e);


template<typename Iter, typename T>
void report_find(const char* info, Iter b, Iter e, T value);


int main()
{
    vector<int> vi{1,2,3,4,5,6};
    list<string> ls{"one", "two", "three", "four", "five"};
    report_find("find(vector<int>, 1)", vi.cbegin(), vi.cend(), 1);
    report_find("find(vector<int>, 3)", vi.cbegin(), vi.cend(), 6);
    report_find("find(vector<int>, 42)", vi.cbegin(), vi.cend(), 42);
    report_find("find(list<string>, 'one'", ls.cbegin(), ls.cend(), "one");
    report_find("find(list<string>, 'five'", ls.cbegin(), ls.cend(), "five");
    report_find("find(list<string>, 'foo'", ls.cbegin(), ls.cend(), "foo");
}


template<typename Iter, typename T>
Iter find(Iter b, Iter e, T value)
{
    while( b != e && *b != value )
        ++b;
    return b;
}

template<typename Iter>
void print_containter(Iter b, Iter e)
{
    while( b != e ){
        std::cout << *b;
        if( ++b != e ) std::cout << ", ";
    }
}

template<typename Iter, typename T>
void report_find(const char* info, Iter b, Iter e, T value)
{
    Iter res = find(b, e, value);
    std::cout << info << ": value " << (res != e ? "found." : "not found.")
              << std::endl;
}
