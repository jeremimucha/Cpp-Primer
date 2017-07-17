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
using std::endl;
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
        , white(ws)
        , sensitive(case_sensitive)
        , trimmode(trim)
        { }
    
    void whitespace(const std::string& ws)
        { white = ws; }
    bool is_whitespace(char c)
        { return white.find(c) != std::string::npos; }
    
    void case_sensitive(bool b)
        { sensitive = b; }
    bool is_case_sensitive()
        { return sensitive; }
    void trim_mode(bool b)
        { trimmode = b; }
    bool is_trim_mode()
        { return trimmode; }

    PunctStream& operator>>(string& s);
    operator bool();
private:
    std::string& trimws(std::string& word)
    {
        std::string::size_type pos = word.find_first_not_of(white);
        if( pos == std::string::npos  )
            return (word = "");
        word.erase(0,pos+1);
        pos = word.find_last_not_of(white);
        word.erase(pos);
        return word;
    }
    std::string& lower(std::string& word)
    {
        if(sensitive)
            std::transform(word.begin(), word.end(), word.begin(),
                [this](char ch)->char { return ::tolower(ch); });
        return word;
    }
    void replacews(std::string& line)
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
        if(trimmode)
            lower(trimws(line));
        else
            replacews(line);
                        
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
    if( argc != 2 ){
        std::cerr << "Usage: " << __FILE__ << " infile\n";
        exit(EXIT_FAILURE);
    }

    std::ifstream ifs{argv[1]};
    if(!ifs.is_open()){
        std::cerr << "Failed to open the file " << argv[1] << "\n";
        exit(EXIT_FAILURE);
    }

    map<size_t, size_t> word_count;

    PunctStream pin(ifs, false, false, ",./\\\'\"?|:;[{]}!@#$%^&*()");
    string word;
    while( pin >> word ){
        // ++word_count[std::move(word)];
        ++word_count.insert(std::make_pair(word.size(),0)).first->second;
    }

    for(map<size_t,size_t>::const_iterator it = word_count.cbegin();
        it != word_count.cend() && (it->first < 11); ++it){
            cout << "words sized " << it->first << " occur " << it->second
                 << std::endl;
    }

    cout << "\nDone.";
}
