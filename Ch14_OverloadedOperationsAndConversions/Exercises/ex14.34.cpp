// ex 14.34.cpp
/*Define a function-object class to perform an if-then-else
operation: The call operator for this class should take three parameters. It
should test its first parameter and if that test succeeds, it should return its
second parameter; otherwise, it should return its third parameter.*/
#include <iostream>
#include <string>


class IfThenElse
{
public:
    std::string operator()(bool test, const std::string& iftrue, const std::string& iffalse)
        { return (test ? iftrue : iffalse); }
};


int main()
{
    IfThenElse test;
    int i{0};
    std::cout << "i == 0: " << test(i == 0, "True", "False") << std::endl;
    std::cout << "i > 0: " << test( i > 0, "True", "False") << std::endl;
    ++i;
    std::cout << "i > 0: " << test(i > 0, "True", "False") << std::endl;
}
