// ex9.49.cpp
/*A letter has an ascender if, as with  d or  f , part of the
letter extends above the middle of the line. A letter has a descender if, as
with  p or  g , part of the letter extends below the line. Write a program that
reads a file containing words and reports the longest word that contains
neither ascenders nor descenders.*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cstdlib>
using std::vector;
using std::string;
using std::cout;


bool has_asc_desc(const string& s);


int main(int argc, char* argv[])
{
    if(argc != 2){
        std::cout << "Usage: " << argv[0] << " file_name\n";
        exit(EXIT_FAILURE);
    }

    std::ifstream ifs{argv[1]};
    if( !ifs.is_open() ){
        std::cout << "Failed to open the file " << argv[1] << "\n";
        exit(EXIT_FAILURE);
    }

    vector<string> words;
    for(string s; ifs >> s; ){
        if(!has_asc_desc(s))
            words.push_back(std::move(s));
    }

    cout << "Words with no ascenders or descenders:\n";
    for(const auto& w : words) std::cout << w << "\n";

    cout << "\nLongest word withouth ascenders or descenders:\n\t";
    string longest = words.front();
    for(auto it = ++words.cbegin(); it!=words.cend(); ++it){
        if( longest.size() < it->size() )
            longest = *it;
    }
    cout << longest << ", size = " << longest.size();

    cout << "\n\nDone.\n";
    return 0;
}


bool has_asc_desc(const string& s)
{
    static const string ascdesc{"qtypdfghjkl"};
    return s.find_first_of(ascdesc) != string::npos;
}
