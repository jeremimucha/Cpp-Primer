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

// this will generate a compilation error
    // std::cout << "compare(sd1, sd2) = " << compare(sd1, sd2) << std::endl;
// compiler spits this out:
/* ex16.2.cpp: In instantiation of 'int compare(const T&, const T&) [with T = Sales_data]':
ex16.2.cpp:21:60:   required from here
ex16.2.cpp:27:13: error: no match for 'operator<' (operand types are 'const Sales_data' and 'const Sales_data')
     if( lhs < rhs ) return -1;
         ~~~~^~~~~
ex16.2.cpp:27:13: note: candidate: operator<(double, double) <built-in>
ex16.2.cpp:27:13: note:   no known conversion for argument 2 from 'const Sales_data' to 'double'
ex16.2.cpp:28:13: error: no match for 'operator<' (operand types are 'const Sales_data' and 'const Sales_data')
     if( rhs < lhs ) return 1;
         ~~~~^~~~~
ex16.2.cpp:28:13: note: candidate: operator<(double, double) <built-in>
ex16.2.cpp:28:13: note:   no known conversion for argument 2 from 'const Sales_data' to 'double'
 */
}

template<typename T>
int compare(const T& lhs, const T& rhs)
{
    if( lhs < rhs ) return -1;
    if( rhs < lhs ) return 1;
    return 0;
}
