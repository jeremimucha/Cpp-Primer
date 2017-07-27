// variadic templates
#include <iostream>
#include <string>
using std::cout;
using std::endl;


// function to end the recursion and print the last element
// this function needs to be declared before the variadic version of print is defined
template<typename T>
std::ostream& print(std::ostream& os, const T& t);

// this version of print will be called for all but the last element in the pack
template<typename T, typename... Args>
std::ostream& print(std::ostream& os, const T&, const Args&... rest);

struct noOutput
{
    noOutput();
};

int main()
{
    print(std::cout, "one");
    cout << endl;
    print(std::cout, "one", 2);
    cout << endl;
    print(std::cout, "one", 2, '3', std::string("std::string"), 4.2);
    print(std::cout, "one", noOutput());
}


template<typename T>
std::ostream& print(std::ostream& os, const T& t)
{
    return os << t;     // no separator after the last element in the pack
}

template<typename T, typename... Args>
std::ostream& print(std::ostream& os, const T& t, const Args&... rest)
{
    os << t << ", ";            // print the first argument
    return print(os, rest...);  // recursive call, print the other arguments
}
