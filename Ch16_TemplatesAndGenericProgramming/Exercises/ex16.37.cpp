/* Exercise 16.37: The library  max function has two function parameters and
returns the larger of its arguments. This function has one template type
parameter. Could you call  max passing it an  int and a  double ? If so, how? If
not, why not? */
#include <iostream>
#include <algorithm>


int main()
{
    int i = 42;
    double d = 4.2;
    auto bigger = std::max<double>(i,d);
    std::cout << "std::max(42, 4.2) = " << bigger << std::endl;
}
