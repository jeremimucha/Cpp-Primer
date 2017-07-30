/* Exercise 17.29: Allow the user to supply a seed as an optional argument
to the function you wrote in the previous exercise. */
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


unsigned int randint(unsigned s = time(nullptr));


int main()
{
    for(int i=0; i<10; ++i)
        cout << randint() << " ";
}


unsigned int randint(unsigned s)
{
    static default_random_engine e(s);
    static uniform_int_distribution<unsigned> u(0, 42);
    // e.seed(s);
    return u(e);
}
