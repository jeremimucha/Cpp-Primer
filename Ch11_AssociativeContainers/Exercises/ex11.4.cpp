// ex11.4.cpp
/*11.3: Write your own version of the word-counting program.
11.4: Extend your program to ignore case and punctuation. For
example, “example.” “example,” and “Example” should all increment the
same counter.*/
#include <iostream>
#include <fstream>
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


string& remove_punct(string& str);
inline string& to_lower(string& str);


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
    while( ifs >> word ){
        if(!to_lower( remove_punct(word) ).empty() &&
            exclude.find(word) == exclude.end()){
            ++word_count[std::move(word)];
        }
    }
    for(map<string, size_t>::const_iterator it=word_count.cbegin();
        it!=word_count.cend(); ++it){
            cout << it->first << " occurs " << it->second
                 << ((it->second > 1) ? " times" : " time")
                 << std::endl;
        }

    cout << "\nDone.";
}


string& remove_punct(string& str)
{
    static std::set<char> punct{',','.','?','!',';',':'};
    // for(const char c : punct){
    //     string::size_type pos{};
    //     while( (pos = str.rfind(c)) != string::npos )
    //         str.erase(pos);
    // }
    for(char ch=str.back(); punct.find(ch) != punct.end(); ch=str.back()){
        str.erase(str.size()-1);
    }
    return str;
}

inline string& to_lower(string& str)
{
    std::transform(str.cbegin(), str.cend(), str.begin(), ::tolower);
    return str;
}