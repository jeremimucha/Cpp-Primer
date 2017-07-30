/* Exercise 17.30: Revise your function again this time to take a minimum
and maximum value for the numbers that the function should return. */
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
using std::cout;
using std::endl;
using std::vector;
using std::default_random_engine;
using std::uniform_int_distribution;
using std::time;


unsigned int randint(unsigned min, unsigned max, unsigned s = time(nullptr));


int main()
{
    for(int i=0; i<10; ++i)
        cout << randint(11, 9999) << " ";
}


unsigned int randint(unsigned min, unsigned max, unsigned s)
{
    static default_random_engine e(s);
    static uniform_int_distribution<unsigned> u(min, max);
    // e.seed(s);
    return u(e);
}
