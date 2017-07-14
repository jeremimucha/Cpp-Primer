// ex 14.38
/*Write a class that tests whether the length of a given
string matches a given bound. Use that object to write a program to
report how many words in an input file are of sizes 1 through 10 inclusive.*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>      // exit, EXIT_FAILURE
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <utility>
using std::cout;
using std::cin;
using std::string;
using std::map;
using std::set;
using std::pair;


/* ------------------------------------------------------------------------- */
class PunctStream
{
public:
    explicit PunctStream(std::istream& is)
        : source(is), sensitive(true), trimmode(true) { }
    PunctStream(std::istream& is, bool case_sensitive, bool trim, const string& ws)
        : source(is)
        , white(ws.cbegin(), ws.cend())
        , sensitive(case_sensitive)
        , trimmode(trim)
          { }
    PunctStream(std::istream& is, bool case_sensitive, std::set<char> ws)
        : source(is),
          white(ws),
          sensitive(case_sensitive)
          { }
    
    void whitespace(std::set<char>& ws)
         { white = ws; }
    void whitespace(const string& ws)
        { white = std::set<char>(ws.cbegin(), ws.cend()); }
    bool is_whitespace(char c)
        { return white.find(c) != white.end(); }
    
    void case_sensitive(bool b)
        { sensitive = b; }
    bool is_case_sensitive()
        { return sensitive; }

    PunctStream& operator>>(string& s);
    operator bool();
private:
    static std::string& trimws(std::string& word)
    {
        std::string::size_type pos = word.find_first_not_of(white);
        word.erase(0,pos+1);
        pos = word.find_last_not_of(white);
        word.erase(pos);
        return word;
    }
    static void replacews(std::string& line)
    {
        std::transform(line.begin(), line.end(), line.begin(),
            [this](char ch) -> char
              { return is_whitespace(ch) ? ' '
                        : (sensitive ? ch : ::tolower(ch)); });
    }

    std::istream& source;       // character source
    std::istringstream buffer;  // we let buffer do our formatting
    std::string white;          // characters considered "whitespace"
    bool sensitive;             // is the stream case sensitive?
    bool trimmode;              // trim ws off of ends or scan entire string?
};

PunctStream& PunctStream::operator>>(string& s)
{
    while( !(buffer>>s) ){  // try to read from buffer
        if( buffer.bad() || !source.good() )
            return *this;
        buffer.clear();

        string line;
        getline(source, line);  // get a line from source

        // do character replacement as needed:
        
                        
        buffer.str(std::move(line));
    }
    return *this;
}

inline PunctStream::operator bool()
{
    return !(source.fail() || source.bad()) && source.good();
}
/* ------------------------------------------------------------------------- */



int main(int argc, char* argv[])
{

}
