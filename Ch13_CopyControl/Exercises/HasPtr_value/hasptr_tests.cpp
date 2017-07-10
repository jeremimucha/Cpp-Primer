// minimal test code for the value-like HasPtr class
#include "hasptr_val.h"
#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>

using std::cout;
using std::endl;
using std::vector;


int main()
{
    HasPtr hp1("one");
    // HasPtr hp2("two");
    // HasPtr hp3(hp1);
    // cout << "Before assignment:\n";
    // cout << "hp1: " << hp1 << "\n"
    //      << "hp2: " << hp2 << "\n"
    //      << "hp3: " << hp3 << "\n";
    // hp2 = hp1;
    // cout << "After assignment hp2 = hp1:\n"
    //      << "hp1: " << hp1 << "\n"
    //      << "hp2: " << hp2 << "\n";
    HasPtr hp4("four");
    // cout << "\nBefore std::swap:\n"
    //      << "hp1: " << hp1 << "\n"
    //      << "hp4: " << hp4 << "\n";
    // std::swap(hp1, hp4);
    // cout << "After std::swap:\n"
    //      << "hp1: " << hp1 << "\n"
    //      << "hp4: " << hp4 << "\n";
    cout << "\nafter using std::swap and calling swap(hp1, hp4):\n";
    using std::swap;
    swap(hp1, hp4);
    cout << "hp1: " << hp1 << "\n"
         << "hp4: " << hp4 << "\n";

    cout << "\nCreating a vector of HasPtr objects from an initializer list:\n";
    vector<HasPtr> vhp;
    vhp.reserve(5);
    vhp.emplace_back("555");
    vhp.emplace_back("111");
    vhp.emplace_back("444");
    vhp.emplace_back("333");
    std::sort(vhp.begin(), vhp.end());
}
