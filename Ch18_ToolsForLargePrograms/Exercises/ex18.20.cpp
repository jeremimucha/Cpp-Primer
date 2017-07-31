/* Exercise 18.20: In the following code, determine which function, if any,
matches the call to  compute . List the candidate and viable functions. What
type conversions, if any, are applied to the argument to match the
parameter in each viable function?
Code:
namespace primerLib {
void compute();
void compute(const void *);
}
using primerLib::compute;
void compute(int);
void compute(double, double = 3.4);
void compute(char*, char* = 0);
void f()
{
compute(0);
}
What would happen if the  using declaration were located in  main before the call
to  compute? Answer the same questions as before. */
#include <iostream>


namespace primerLib {
    void compute();
    void compute(const void *);
}

// using primerLib::compute;    // compute(int) will be called
void compute(int);
void compute(double, double = 3.4);
void compute(char*, char* = 0);

void f()
{
    // using primerLib::compute;    // will call compute(const void*)
    compute(0);
}


int main()
{
    // using primerLib::compute;    // will call compute(int)
    f();
}


void primerLib::compute()
{
    std::cout << "primerLib::compute()" << std::endl;
}
void primerLib::compute(const void *)
{
    std::cout << "primerLib::compute(const void*)" << std::endl;
}

void compute(int)
{
    std::cout << "compute(int)" << std::endl;
}
void compute(double, double)
{
    std::cout << "compute(double, double=3.4)" << std::endl;
}
void compute(char*, char*)
{
    std::cout << "compute(char*, char* = 0)" << std::endl;
}
