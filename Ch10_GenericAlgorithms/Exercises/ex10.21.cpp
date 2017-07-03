// ex10.21.cpp
/*Write a lambda that captures a local  int variable and
decrements that variable until it reaches 0. Once the variable is 0
additional calls should no longer decrement the variable. The lambda
should return a  bool that indicates whether the captured variable is 0.*/
#include <iostream>


int main()
{
    int i = 7;
    auto f = [i]() mutable -> bool { return --i == 0; };
    for(int count{1}; !f(); ++count){
        std::cout << "Number of f() calls = " << count << "\n";
    }
}
