/* Exercise 18.5: Modify the following  main function to catch any of the
exception types shown in Figure 18.1 (p. 783):
Code:
int main() {
// use of the C++ standard library
}
The handlers should print the error message associated with the exception
before calling  abort (defined in the header  cstdlib ) to terminate  main . */
#include <iostream>
#include <stdexcept>
#include <cstdlib>



int main()
try{
    throw std::runtime_error("runtime error thrown from main");
}
catch(std::exception& e){
    std::cerr << e.what();
    std::abort();
}
