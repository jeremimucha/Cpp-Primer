#include <iostream>
#include <utility>
#include <vector>
#include "String.h"


void info(const String& s, const char*);


int main()
{
    String s1("Foo");
    String s2("Foo");
    std::cout.setf(std::ios_base::boolalpha);
    std::cout << "s1 == s2: " << (s1 == s2) << std::endl;
    String s3("Bar");
    std::cout << "s1 == s3: " << (s1 == s3) << std::endl;
    std::cout << "s1 != s3: " << (s1 != s3) << std::endl;
}


void info(const String& s, const char* msg)
{
    std::cout << msg << s << "\n\t"
              << "size: " << s.size() << ", capacity: " << s.capacity()
              << std::endl;
}
