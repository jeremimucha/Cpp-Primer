// minimal test code for the pointer-like HasPtr class
#include <iostream>
#include "hasptr_ptr.h"
using namespace std;


int main()
{
    HasPtr hp1("one");
    HasPtr hp2("two");
    HasPtr hp3(hp1);
    cout << "Before assignment:\n";
    cout << "hp1: " << hp1 << "\n"
         << "hp2: " << hp2 << "\n"
         << "hp3: " << hp3 << "\n";
    hp2 = hp1;
    cout << "After assignment hp2 = hp1:\n"
         << "hp1: " << hp1 << "\n"
         << "hp2: " << hp2 << "\n";
}
