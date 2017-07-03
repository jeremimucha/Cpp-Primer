// ex10.29b.cpp
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
    istream_iterator<string> is_iter(ifs);
    istream_iterator<string> is_end;

    // read all the words from the file (stream)
    while( is_iter != is_end ){
        // *is_iter++ reads from the stream,
        // returns the old value and accesses it by dereferencing the iterator
        words.push_back(*is_iter++);
    }

    ostream_iterator<string> os_iter(std::cout, "\n");
    for(auto it = words.cbegin(); it!=words.cend();){
        // *os_iter++
        // the assignment operator of the ostream_iterator writes elements to cout
        // dereference and postincrement do nothing, but are used
        // for consistency with other iterators
        *os_iter++ = *it++;
    }
    std::cout << std::endl;
}
