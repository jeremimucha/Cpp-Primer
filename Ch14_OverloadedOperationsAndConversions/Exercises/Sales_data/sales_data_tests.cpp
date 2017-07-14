#include <iostream>
#include "Sales_data.h"
using std::cout;
using std::endl;


int main()
{
    Sales_data sd1("foo", 11, 3.14);
    Sales_data sd2("foo", 42, 11.11);
    Sales_data sd3 = sd1 + sd2;
    Sales_data sd4("foo", 9, 2.36);
    cout << "sd1: " << sd1 << "\n"
         << "sd2: " << sd2 << "\n"
         << "sd3 == sd1 + sd2: " << sd3 << "\n"
         << "sd4: " << sd4 << "\n";
    sd4 += sd2;
    cout << "sd4 += sd2: " << sd4 << "\n";
    sd4 = "foobar";
    cout << "sd4 = foobar: " << sd4 << "\n";
}
