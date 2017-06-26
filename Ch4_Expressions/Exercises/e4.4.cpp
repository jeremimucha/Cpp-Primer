// e4.4.cpp -- Ch4 - operator precendence
#include <iostream>


int main()
{
    std::cout << "12 / 3 * 4 + 5 * 15 + 24 % 4 / 2 = "
              << 12 / 3 * 4 + 5 * 15 + 24 % 4 / 2
              << std::endl;
    std::cout << "((12 / 3) * 4) + (5 * 15) + ((24 % 4) / 2) = "
              << ((12 / 3) * 4) + (5 * 15) + ((24 % 4) / 2);
}
