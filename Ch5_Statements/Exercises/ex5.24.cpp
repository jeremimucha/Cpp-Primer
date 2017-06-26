// ex5.23.cpp -- Chapter 5 exercise 5.23
// Write a program that reads two integers from the stdin and prints the result
// of dividing the first number by the second.
#include<iostream>
#include <stdexcept>

int get_int(std::istream& is, const char* msg, const char* errmsg);

int main()
{
    using namespace std;
    const char* msg = "Please enter an integer\n";
    const char* errmsg = "Invalid argument. Please enter an integral value - e.g. 42.\n"; 
    int a = get_int(cin, msg, errmsg);
    int b = get_int(cin, msg, errmsg);
    if(b == 0)
        throw std::runtime_error("Invalid argument. b can't be 0.\n");
    cout << a << "/" << b << " = " << static_cast<double>(a)/b;
}


int get_int(std::istream& is, const char* msg, const char* errmsg)
{
    int val;
    std::cout << msg;
    while(std::cout << ">> "){
        if( !(is >> val) ){
            std::cout << errmsg;
            is.clear();
            while(is.get() != '\n')
                ;
            continue;
        }
        else{
            while(is.get() != '\n')
                ;
            return val;
        }
    }
}
