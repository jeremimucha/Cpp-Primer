// exs9.2.1.cpp -- Chapter 9 exercise section 9.2.1
/*9.4: Write a function that takes a pair of iterators to a
vector<int> and an  int value. Look for that value in the range and return a
bool indicating whether it was found.
9.5: Rewrite the previous program to return an iterator to the
requested element. Note that the program must handle the case where the
element is not found.*/
#include <iostream>
#include <vector>


template<typename Iter>
bool containsint(const Iter begin, const Iter end, int seek);

template<typename Iter>
Iter findint(const Iter begin, const Iter end, int seek);


int main()
{
    std::vector<int> v { 9, 1, 4, 0, 12, 11, 42, 56, 36, 81 };

    std::cout << "Calling containsint(v.cbegin(), v.cend(), 42):\n";
    bool contains42 = containsint(v.cbegin(), v.cend(), 42);
    std::cout.setf(std::ios_base::boolalpha);
    std::cout << "v contains 42 = " << contains42;

    std::cout << "\n\nCalling findint(v.cbegin(), v.cend(), 42):";
    std::vector<int>::const_iterator it = findint(v.cbegin(), v.cend(), 42);
    std::cout << "\nv contains 42 = " << (it != v.cend() ? true : false);
    std::cout << "\nvalues starting at 42 up to the end of the container:\n";
    for( ; it!=v.cend(); ++it)
        std::cout << *it << ", ";

    std::cout << "\nDone.\n";
    return 0;
}


template<typename Iter>
bool containsint(Iter begin, Iter end, int seek)
{
    while(begin != end){
        if( *begin++ == seek)
            return true;
    }
    return false;
}

template<typename Iter>
Iter findint(Iter begin, Iter end, int seek)
{
    while(begin != end){
        if( *begin == seek )
            break;
        ++begin;
    }
    return begin;
}
