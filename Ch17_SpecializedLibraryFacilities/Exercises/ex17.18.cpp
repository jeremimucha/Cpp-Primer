/* Exercise 17.17: Update your program so that it finds all the words in an
input sequence that violiate the “ei” grammar rule. */
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::regex;
using std::smatch;
using std::sregex_iterator;
using std::vector;
using std::set;
using std::pair;
using std::partition;


string pattern("[[:alpha:]]*[^c]ei[[:alpha:]]*");
regex re(pattern, regex::icase);
set<string> exceptions{"albeit", "neighbor"};


int main()
{
    string line;
    cout << "Check if the input violates the 'i before e except after c' rule."
         << " Empty line to quit.\n";
    
    while(cout << ">> " && getline(cin, line) && !line.empty()){
        vector<smatch> matches;
        for(sregex_iterator it(line.begin(), line.end(), re), end_it;
            it != end_it; /* ++it */ ){
                matches.push_back(std::move(*it++));
        }
        vector<smatch>::iterator ppoint = partition(matches.begin(), matches.end(),
                        [](const smatch& m)
                        { return exceptions.find(m.str()) == exceptions.end(); });
        if(matches.begin() == ppoint)
            cout << "no violations";
        else{
            cout << "violations: ";
            for(vector<smatch>::const_iterator it = matches.cbegin();
                it != ppoint; ++it){
                cout << it->str() << ", ";
            }
        }
        if(ppoint != matches.end()){
            cout << "\nexceptions to the rule: ";
            for(; ppoint != matches.end(); ++ppoint)
                cout << ppoint->str() << ", ";
        }
        cout << endl;
    }
}
