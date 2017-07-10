// minimal test code for the Employee class
#include <iostream>
#include "employee.h"
using namespace std;


int main()
{
    Employee e1{"Foo"};
    Employee e2{"Bar"};
    Employee e3{e1};
    cout << "Before assignment:\n";
    cout << "e1: " << e1 << "\n"
         << "e2: " << e2 << "\n"
         << "e3: " << e3 << "\n";
    e2 = e1;
    cout << "After assignment:\n";
    cout << "e2 = e1:\n"
         << "\te1: " << e1
         << "\n\te2: " << e2;

}
