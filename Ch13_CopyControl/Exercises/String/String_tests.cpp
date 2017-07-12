#include <iostream>
#include <utility>
#include "String.h"


int main()
{
    using std::swap;
    String s1;  // default ctor
    String s2("Test String");
    String s3(s2);
    s2.append(" 2");
    s3.push_back(' ');
    s3.push_back('3');
    s1 = s3;
    s1.resize(s1.size() - 2);
    s1.append(" 1");
    std::cout << "s1: " << s1 << "\n";
    std::cout << "s2: " << s2 << "\n";
    std::cout << "s3: " << s3 << "\n";
}
