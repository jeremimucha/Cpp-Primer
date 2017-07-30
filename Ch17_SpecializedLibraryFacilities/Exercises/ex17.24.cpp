/* Exercise 17.24: Write your own version of the program to reformat
phone numbers. */
#include <iostream>
#include <string>
#include <regex>
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::regex;
using std::smatch;
using std::regex_replace;
using std::regex_constants::format_no_copy;


string phonepat = "(\\()?(\\d{3})(\\))?([-.]|[ ]*)?(\\d{3})([-.]|[ ]*)?(\\d{4})";
regex re_phone(phonepat);
// 2nd subregex followed by a '.' followed by a 5th subregex
// followed by a '.' followed by a 7th subregex
string fmt = "$2.$5.$7";


int main()
{
    string line;
    cout << "Reformat phone numbers to ddd.ddd.dddd. Empty line to quit.\n";
    while(cout << ">> " && getline(cin, line) && ! line.empty()){
        // regex_replace outputs the entire match by defualt - even the unmatched part
        // format_no_copy cuts the output down to the matched part
        cout << regex_replace(line, re_phone, fmt, format_no_copy) << endl;
    }
}
