/* Exercise 17.15: Write a program using the pattern that finds words that
violate the  “i before  e except after  c” rule. Have your program prompt the
user to supply a word and indicate whether the word is okay or not. Test
your program with words that do and do not violate the rule. */
#include <iostream>
#include <string>
#include <regex>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::regex;
using std::smatch;
using std::regex_search;


string pattern("[[:alpha:]]*[^c]ei[[:alpha:]]*");
regex re(pattern);
smatch results;


int main()
{
    string line;
    cout << "Check if the input violates the 'i before e except after c' rule. "
         << "Empty line to quit.\n";
    while(cout <<">> " && getline(cin, line) && !line.empty()){
        if(regex_search(line, results, re)){
            cout << "violation: " << results.str();
        }
        else
            cout << "no violations";
        cout << endl;
    }
}
