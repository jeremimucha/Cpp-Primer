// ex10.28.cpp
/*Copy a  vector that holds the values from  1 to  9 inclusive,
into three other containers. Use an  inserter , a  back_inserter , and a
front_inserter , respectivly to add elements to these containers. Predict
how the output sequence varies by the kind of inserter and verify your
predictions by running your programs.*/
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
using std::cout;
using std::endl;
using std::vector;
using std::list;


template<typename T>
void print_container(T begin, T end)
{
    while( begin != end ){
        cout << *begin;
        if( ++begin != end )
            cout << ", ";
    }
}


int main()
{
    vector<int> vi{1,2,3,4,5,6,7,8,9};
    list<int> li1;
    list<int> li2;
    list<int> li3;

    cout << "vi: ";
    print_container(vi.cbegin(), vi.cend());

    std::copy(vi.cbegin(), vi.cend(), std::front_inserter(li1));
    std::copy(vi.cbegin(), vi.cend(), std::inserter(li2, li2.begin()));
    std::copy(vi.cbegin(), vi.cend(), std::back_inserter(li3));
    cout << "\nli1 - front_inserter: ";
    print_container(li1.cbegin(), li1.cend());
    cout << "\nli2 - inserter: ";
    print_container(li2.cbegin(), li2.cend());
    cout << "\nli3 - back_inserter: ";
    print_container(li3.cbegin(), li3.cend());

    list<int> li4;
    list<int> li5;
    list<int> li6;
    std::copy(vi.cbegin(), vi.cend(), std::front_insert_iterator<list<int>>(li4));
    std::copy(vi.cbegin(), vi.cend(), std::insert_iterator<list<int>>(li5, li5.begin()));
    std::copy(vi.cbegin(), vi.cend(), std::back_insert_iterator<list<int>>(li6));
    cout << "\nli4 - front_insert_iterator<list<int>>: ";
    print_container(li4.cbegin(), li4.cend());
    cout << "\nli5 - insert_iterator<list<int>>: ";
    print_container(li5.cbegin(), li5.cend());
    cout << "\nli6 - back_insert_iterator<list<int>>: ";
    print_container(li6.cbegin(), li6.cend());
}
