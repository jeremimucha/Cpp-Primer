// ex9.31.cpp
/*The program on page 354 to remove even-valued
elements and duplicate odd ones will not work on a  list or  forward_list .
Why? Revise the program so that it works on these types as well.*/
#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
using std::vector;
using std::list;
using std::forward_list;
using std::cout;
using std::endl;


template<typename Iter>
void print_container(Iter begin, Iter end);


int main()
{
// vector RandomIterator - can increment arbitrary number of steps
    vector<int> vi{0,1,2,3,4,5,6,7,8,9};
    cout << "vector before modification: ";
    print_container(vi.cbegin(), vi.cend());
    for( auto it=vi.cbegin(); it!=vi.cend(); ){
        if( *it % 2 ){
            // inserts *it before it, returns iterator to the inserted element
            it = vi.insert(it, *it);
            it += 2;    // skip over inserted and original element
        }
        else{
            // erases elem pointed to by it, returns iterator to the elem after it
            it = vi.erase(it);
        }
    }
    cout << "\nvector after modification: ";
    print_container(vi.cbegin(), vi.cend());

// list - BidirectionalIterator - can only increment by a single elem at a time
    list<int> li{0,1,2,3,4,5,6,7,8,9};
    cout << "\n\nlist before modification: ";
    print_container(li.cbegin(), li.cend());
    for( auto it=li.cbegin(); it!=li.cend(); ){
        if( *it % 2 ){
            it = li.insert(it, *it);
            ++it; ++it;
        }
        else{
            it = li.erase(it);
        }
    }
    cout << "\nlist after modification: ";
    print_container(li.cbegin(), li.cend());

// forward_list - ForwardIterator - can increment a single elem at a time
// insert_after - elements are inserted after the one pointed to
// erase_after - elements are removed after the one pointed to
    forward_list<int> fli{0,1,2,3,4,5,6,7,8,9};
    cout << "\n\nforward_list before modification: ";
    print_container(fli.cbegin(), fli.cend());
    for( auto curr=fli.cbegin(), prev=fli.cbefore_begin();
        curr != fli.cend();)
        {
            if( *curr % 2 ){
                curr = fli.insert_after(curr, *curr);
                ++curr; // skip over the inserted element
                ++prev; ++prev; // skip to the inserted element (i.e. the one before curr)
            }
            else{
                curr = fli.erase_after(prev);
                // curr is effectively iterated to the next elem
                // prev still points to the elem before curr
            }
        }
    cout << "\nforward_list after modification: ";
    print_container(fli.cbegin(), fli.cend());

    cout << "\n\nDone.\n";
    return 0;
}


template<typename Iter>
void print_container(Iter begin, Iter end)
{
    while( begin != end ){
        std::cout << *begin;
        if( ++begin != end )
            std::cout << ", ";
    }
    std::cout << std::flush;
}
