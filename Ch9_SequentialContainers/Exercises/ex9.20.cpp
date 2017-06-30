// ex9.20.cpp
/*Write a program to copy elements from a  list<int> into
two  deque s. The even-valued elements should go into one  deque and the
odd ones into the other.*/
#include <iostream>
#include <list>
#include <deque>


template<typename Iter>
void print_container(Iter begin, Iter end);


int main()
{
    std::list<int> lsti{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    std::deque<int> di_even;
    std::deque<int> di_odd;

    for(auto it=lsti.cbegin(); it!=lsti.cend(); ++it){
        if( (*it % 2) == 0 )
            di_even.push_back(*it);
        else
            di_odd.push_back(*it);
    }

    std::cout << "list<int>: ";
    print_container(lsti.cbegin(), lsti.cend());
    std::cout << "\ndeque<int> even: ";
    print_container(di_even.cbegin(), di_even.cend());
    std::cout << "\ndeque<int> odd: ";
    print_container(di_odd.cbegin(), di_odd.cend());
    std::cout << "\n\nDone.\n";
    return 0;
}

template<typename Iter>
void print_container(Iter begin, Iter end)
{
    while(begin != end){
        std::cout << *begin;
        if( ++begin != end )
            std::cout << ", ";
    }
}
