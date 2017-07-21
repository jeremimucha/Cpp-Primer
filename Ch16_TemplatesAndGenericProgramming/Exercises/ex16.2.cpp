/* Exercise 16.2
Write and test your own versions of the  compare functions.
Exercise 16.3: Call your  compare function on two  Sales_data objects to see
how your compiler handles errors during instantiation.
*/
#include <iostream>
#include "incl/sales_data.h"


template<typename T>
int compare(const T& lhs, const T& rhs);


int main()
{
    int a = 1, b = 1, c = 0;
    std::cout << "compare(a, b) = " << compare(a, b) << std::endl;
    std::cout << "compare(a, c) = " << compare(a, c) << std::endl;
    Sales_data sd1("Book 1", 11, 3.14);
    Sales_data sd2("Book 2", 11, 3.14);
    std::cout << "compare(sd1, sd2) = " << compare(sd1, sd2) << std::endl;
}

template<typename T>
int compare(const T& lhs, const T& rhs)
{
    if( lhs < rhs ) return -1;
    if( rhs < lhs ) return 1;
    return 0;
}
