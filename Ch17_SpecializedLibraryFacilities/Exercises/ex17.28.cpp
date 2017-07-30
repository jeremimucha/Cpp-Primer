/* Exercise 17.28: Write a function that generates and returns a uniformly
distributed random  unsigned int each time it is called. */
#include <iostream>
#include <vector>
#include <random>
using std::cout;
using std::endl;
using std::vector;
using std::default_random_engine;
using std::uniform_int_distribution;


unsigned int randint();


int main()
{
    for(int i=0; i<10; ++i)
        cout << randint() << " ";
}


unsigned int randint()
{
    static default_random_engine e;
    static uniform_int_distribution<unsigned> u(0, 42);
    return u(e);
}