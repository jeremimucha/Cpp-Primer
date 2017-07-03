// ex10.29.cpp
/*Write a program using stream iterators to read a text file
into a  vector of  string s.*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cstdlib>
using std::vector;
using std::string;
using std::istream_iterator;
using std::ostream_iterator;


int main(int argc, char* argv[])
{
    if(argc != 2){
        std::cerr << "Usage: " << argv[0] << " filename.\n";
        exit(EXIT_FAILURE);
    }

    std::ifstream ifs{argv[1]};
    if(!ifs.is_open()){
        std::cerr << "Failed to open the file " << argv[1];
        exit(EXIT_FAILURE);
    }

    vector<string> words;
    std::copy(istream_iterator<string>(ifs), istream_iterator<string>(),
              std::back_inserter(words));
    std::cout << "Words from the " << argv[1] << " file, each on a separate line:\n";
    std::copy(words.cbegin(), words.cend(), ostream_iterator<string>(std::cout, "\n"));
}
