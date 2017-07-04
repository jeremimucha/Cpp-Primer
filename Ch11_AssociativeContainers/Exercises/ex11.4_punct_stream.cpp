// ex11.4.cpp
/*11.3: Write your own version of the word-counting program.
11.4: Extend your program to ignore case and punctuation. For
example, “example.” “example,” and “Example” should all increment the
same counter.*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>  // exit, EXIT_FAILURE
#include <set>
#include <map>
#include <algorithm>
#include <utility>
using std::cout;
using std::string;
using std::map;
using std::set;
using std::pair;


/* ------------------------------------------------------------------------- */
class PunctStream
{
public:
    explicit PunctStream(std::istream& is)
        : source(is), sensitive(true) { }
    PunctStream(std::istream& is, bool case_sensitive, const string& ws)
        : source(is),
          white(ws.cbegin(), ws.cend()),
          sensitive(case_sensitive)
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
    std::istream& source;       // character source
    std::istringstream buffer;  // we let buffer do our formatting
    std::set<char> white;       // characters considered "whitespace"
    bool sensitive;             // is the stream case sensitive?
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
        std::transform(line.begin(), line.end(), line.begin(),
            [this](char ch) -> char
              { return is_whitespace(ch) ? ' '
                        : (sensitive ? ch : ::tolower(ch)); });
                        
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
    if(argc != 2){
        std::cerr << "Usage: " << __FILE__ << " infile\n";
        exit(EXIT_FAILURE);
    }
    
    std::ifstream ifs{argv[1]};
    if(!ifs.is_open()){
        std::cerr << "Failed to open the file " << argv[1] << "\n";
        exit(EXIT_FAILURE);
    }

    map<string, size_t> word_count;
    set<string> exclude{"The", "the", "But", "but", "And", "and", "Or", "or",
                        "An", "an", "A", "a"};

    string word;
    PunctStream ps(ifs, false, ",.?!:;'");
    while( ps >> word )
        ++word_count[std::move(word)];
    
    for(map<string, size_t>::const_iterator it=word_count.cbegin();
        it!=word_count.cend(); ++it){
            cout << it->first << " occurs " << it->second
                 << ((it->second > 1) ? " times" : " time")
                 << std::endl;
        }

    cout << "\nDone.";
}
