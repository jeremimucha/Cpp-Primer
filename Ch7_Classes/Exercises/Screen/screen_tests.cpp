// screen_tests.cpp -- Chapter 7 Classes - test code for the Screen class
#include <iostream>
#include "screen.h"


int main()
{
    Screen myScreen(5, 5, 'X');
    myScreen.move(4,0).set('#').display(std::cout);
    std::cout << "\n";
    myScreen.display(std::cout);
    std::cout << "\n";
}
