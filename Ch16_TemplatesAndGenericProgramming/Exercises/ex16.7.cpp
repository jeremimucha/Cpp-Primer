/* Exercise 16.7: Write a  constexpr template that returns the size of a given
array.
*/
#include <iostream>
#include <string>


template<typename T, unsigned N>
constexpr unsigned sizearray(T(&)[N]) { return N; }


int main()
{
    int arrint[]{1,2,3,4,5,6,7};
    double arrdouble[]{5.1, .1, .2, .3, .3, .3};
    int onearr[]{1};
    std::cout << "sizearray(arrint) = " << sizearray(arrint) << std::endl;
    std::cout << "sizearray(arrdouble) = " << sizearray(arrdouble) << std::endl;
    std::cout << "sizearray(onearr) = " << sizearray(onearr) << std::endl;
}
