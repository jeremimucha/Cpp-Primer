/* Exercise 17.17: Update your program so that it finds all the words in an
input sequence that violiate the “ei” grammar rule. */
#include <iostream>
#include <string>
#include <regex>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::regex;
using std::smatch;
using std::sregex_iterator;


string pattern("[[:alpha:]]*[^c]ei[[:alpha:]]*");
regex re(pattern, regex::icase);


int main()
{
    string line;
    cout << "Check if the input violates the 'i before e except after c' rule."
         << " Empty line to quit.\n";
    
    while(cout << ">> " && getline(cin, line) && !line.empty()){
        sregex_iterator it(line.begin(), line.end(), re)
                       ,end_it;
        if( it == end_it )
            cout << "no violations";
        else{
            cout << "violations: ";
            for( ; it != end_it; ++it ){
                cout << it->str() << ", ";
            }
        }
        cout << endl;
    }
}
