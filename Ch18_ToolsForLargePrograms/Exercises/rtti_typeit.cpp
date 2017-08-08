/* Exercise 19.9: Write a program similar to the last one in this section to
print the names your compiler uses for common type names. If your
compiler gives output similar to ours, write a function that will translate
those strings to more human-friendly form. */
#include <iostream>
#include <string>
using std::cout;
using std::endl;

class Base
{
public:
    Base() = default;
    virtual ~Base() = default;
};

class Derived : public Base
{
public:
    Derived() = default;
    virtual ~Derived() = default;
};


int main()
{
    int arr[10];
    Derived d;
    Base* p = &d;
    cout << typeid(42).name() << ", "
         << typeid(arr).name() << ", "
         << typeid(std::string).name() << ", "
         << typeid(p).name() << ", "
         << typeid(*p).name() << endl;
}
