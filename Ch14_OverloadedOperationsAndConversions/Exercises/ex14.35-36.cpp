// ex 14.35 and 14.36
/*Exercise 14.35: Write a class like  PrintString that reads a line of input
from an  istream and returns a  string representing what was read. If the
read fails, return the empty  string .
Exercise 14.36: Use the class from the previous exercise to read the
standard input, storing each line as an element in a  vector .*/
#include <iostream>
#include <vector>
#include <string>
using std::cout;
using std::cin;
using std::vector;
using std::string;


class Reader
{
public:
    Reader(std::istream& is, char separator)
        : instream(is), sep(separator)
        { }
    string operator()() const
    {
        if(instream.peek() == '\n')
            return string();
        string s;
        instream >> s;
        s.push_back(sep);
        return s;
    }
private:
    std::istream& instream;
    char sep;
};


int main()
{
    Reader reader(cin, '\n');
    string s;
    vector<string> vs;
    while( !((s = reader()).empty()) ){
        cout << s;
        vs.push_back(s);
    }

    cout << "\nAnd the vector of strings returned by reader:\n";
    for(const string& s : vs)
        cout << s;
        
    cout << "\nDone.";
}
