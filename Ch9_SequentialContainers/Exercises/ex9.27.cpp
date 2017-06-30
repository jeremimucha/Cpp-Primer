// ex9.27.cpp
/*Write a program to find and remove the odd-valued
elements in a  forward_list<int> .*/
#include <iostream>
#include <forward_list>


template<typename Iter>
void print_container(Iter begin, Iter end);


int main()
{
    std::forward_list<int> fli{1,2,3,4,5,6,7,8,9,10,11};
    std::cout << "Before erasure: ";
    print_container(fli.cbegin(), fli.cend());
    // erase odd-valued elements
    for(auto curr = fli.cbegin(), prev = fli.cbefore_begin();
        curr != fli.cend(); )
        {
            if( *curr % 2 ){     // odd value
            // erase the curr, assign curr to the next elem
                curr = fli.erase_after(prev);   
            }
            else{
                prev = curr;
                ++curr;
            }
        }

    std::cout << "\nAfter erasing odd-valued elems: ";
    print_container(fli.cbegin(), fli.cend());
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
