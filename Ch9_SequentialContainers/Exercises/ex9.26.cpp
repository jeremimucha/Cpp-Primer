// ex9.26.cpp
/*Using the following definition of  ia , copy  ia into a  vector
and into a  list . Use the single-iterator form of  erase to remove the
elements with odd values from your  list and the even values from your
vector .
Code:
int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };*/
#include <iostream>
#include <vector>
#include <list>


template<typename Iter>
void print_container(Iter begin, Iter end);


int main()
{
    int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };
    std::vector<int> vi( std::begin(ia), std::end(ia) );
    std::list<int> li( std::begin(ia), std::end(ia) );
    std::cout << "Before erasure:\n";
    std::cout << "vector<int>: ";
    print_container(vi.cbegin(), vi.cend());
    std::cout << "\nlist<int>: ";
    print_container(li.cbegin(), li.cend());
    std::cout << std::endl;

    for(auto it = vi.cbegin(); it!=vi.cend(); ){
        if( *it % 2 )   // odd value
            it = vi.erase(it);
        else
            ++it;
    }

    for(auto it = li.cbegin(); it!=li.cend(); ){
        if( *it % 2 == 0 )
            it = li.erase(it);
        else
            ++it;
    }

    std::cout <<"\nAfter erasing odd-valued elements from vector<int>:\n";
    print_container(vi.cbegin(), vi.cend());
    std::cout << "\nAfter erasing even-valued elements from list<int>:\n";
    print_container(li.cbegin(), li.cend());

    std::cout << "\n\nDone.\n";
    return 0;
}

template<typename Iter>
void print_container(Iter begin, Iter end)
{
    while(begin != end){
        std::cout << *begin;
        if( ++begin != end)
            std::cout << ", ";
    }
}
