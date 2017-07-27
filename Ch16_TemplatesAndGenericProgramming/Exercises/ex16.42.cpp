/* Exercise 16.41: Write a version of  sum with a return type that is
guaranteed to be large enough to hold the result of the addition. */
#include <iostream>


template<typename T, typename U>
auto mysum(T lhs, U rhs) -> decltype(lhs+rhs)
{
    return lhs + rhs;
}


int main()
{
    signed char c1 = 127;
    signed char c2 = 42;
    auto res = mysum(c1, c2);
    std::cout << "c1 = " << static_cast<int>(c1) 
              << ", c2 = " << static_cast<int>(c2)
              << ", mysum(c1,c2) = " << res << std::endl;
}
