#include <iostream>
#include <utility>
#include <vector>
#include "String.h"
using std::cout;

void info(const String& s, const char*);


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
    String s4(5, 'A');
    s4.resize(7);
    info(s1, "s1: ");
    info(s2, "s2: ");
    info(s3, "s3: ");
    info(s4, "s4: ");

    cout << "\n\nex13.48:\n";
    std::vector<String> vs;
    vs.push_back("foo");
    vs.push_back("bar");
    vs.push_back("42");
}


void info(const String& s, const char* msg)
{
    std::cout << msg << s << "\n\t"
              << "size: " << s.size() << ", capacity: " << s.capacity()
              << std::endl;
}
