/* Exercise 16.5: Write a template version of the  print function from §
6.2.4 (p. 217) that takes a reference to an array and can handle arrays of
any size and any element type.
*/
#include <iostream>
#include <string>


template<typename T, unsigned N>
void print_array(const T (&arr)[N]);


int main()
{
    const char* arrstr[]{"one", "two", "three", "four"};
    int arrint[]{1,2,3,4,5,6};
    double arrdouble[]{1.1,2.2,3.3,4.4,5.5};
    std::cout << "arrstr: ";
    print_array(arrstr);
    std::cout << std::endl;
    
    std::cout << "arrint: ";
    print_array(arrint);
    std::cout << std::endl;
    
    std::cout << "arrdouble: ";
    print_array(arrdouble);
    std::cout << std::endl;
}


template<typename T, unsigned N>
void print_array(const T (&arr)[N])
{
    for(std::size_t i=0; i<N;){
        std::cout << arr[i];
        if( ++i < N ) std::cout << ", ";
    }
}
