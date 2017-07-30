/* Exercise 17.20: Write your own version of the program to validate phone
numbers. */
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


string phonepat = "(\\()?(\\d{3})(\\))?([-.]|[ ]*)?(\\d{3})([-.]|[ ]*)?(\\d{4})";
regex re_phone(phonepat);


// using ssub_match elements to validate the phone number
// [0] is the overall match, the subsequent ones represent each
// of the corresponding subexpressions
bool valid(const smatch& m);


int main()
{
    cout << "Enter lines of text containing phone numbers to check if they're valid."
         << " Empty line to stop."
         << endl;
    string line;
    while(cout << ">> " && getline(cin, line) && !line.empty()){
        // for each matching phone number
        for(sregex_iterator it(line.begin(), line.end(), re_phone), end_it;
            it != end_it; ++it){
                if( valid(*it) )
                    cout << "valid: " << it->str() << endl;
                else
                    cout << "not valid: " << it->str() << endl;
            }
    }
}


bool valid(const smatch& m)
{
    // if there is an open parenthesis before the area code
    if(m[1].matched)
        // the area code must be followed by a closed paren
        // and followed immediately by the rest of the number or a space
        return m[3].matched && (m[4].matched == false || m[4].str() == " ");
    else
        // then there can't be a close after the area code
        // the delimiters between the other two components must match
        return !m[3].matched && ( (m[4].str()[0] == ' ' && m[4].str()[0]==' ') 
                                 || m[4].str() == m[6].str());
}
