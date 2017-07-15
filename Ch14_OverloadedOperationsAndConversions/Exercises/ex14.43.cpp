/* ex 14.43: Using library function objects, determine whether a given
int value is divisible by any element in a container of  int s.
*/
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::modulus;
using std::equal_to;
using std::any_of;
using std::find_if;
using std::bind;
using std::placeholders::_1;


int main()
{
    vector<int> primes{3,5,7,11,13,17,19,23,29, 31};
    cout << "Enter an integer to check if it's divisible by one of the first 10 primes.\n"
         << "Empty line to stop.\n";
    string line;
    while(cout << ">> " && std::getline(cin, line) && !line.empty()){
        std::istringstream iss{line};
        for(int i; iss >> i;){
            bool divisible = any_of(primes.cbegin(), primes.cend(),
                bind(equal_to<int>(), bind(modulus<int>(), i, _1), 0) );
            cout << i << (divisible ? " is" : " isn't") 
                 << " divisible.";
            if( divisible ){
                vector<int>::const_iterator divisor =
                    find_if(primes.cbegin(), primes.cend(),
                        bind(equal_to<int>(), bind(modulus<int>(), i, _1), 0) );
                cout << " Divisor: " << *divisor << endl;
            }else
                cout << endl;
            // could have, of course, be done with just find_if
        }
    }
}
