// ex 11.12.cpp
/*Write a program to read a sequence of  string s and  int s,
storing each into a  pair . Store the  pair s in a  vector .*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <iterator>
#include <algorithm>
#include <cstdlib>
using std::cout;
using std::cin;
using std::pair;
using std::string;
using std::vector;
using std::make_pair;
using std::istream_iterator;
using std::back_inserter;
using std::swap;


template<typename Iter>
void print_container(Iter begin, Iter end);
std::ostream& operator<<(std::ostream& os, const pair<string,int>& p);
std::istream& operator>>(std::istream& is, pair<string,int>& p);


int main(int argc, char* argv[])
{
    if(argc != 2){
        std::cerr << "Usage: " << argv[0] << " inputfile\n";
        exit(EXIT_FAILURE);
    }
    std::ifstream ifs{argv[1]};
    if(!ifs.is_open()){
        std::cerr << "Failed to open the file " << argv[1] << "\n";
        exit(EXIT_FAILURE);
    }

// naively read strings and ints and manually construct a pair
    vector<pair<string,int>> vpsi1;
    string s;
    int i;
    while( ifs >> s >> i )
        vpsi1.push_back(pair<string,int>(std::move(s),i));

    cout << "vpsi1 (manually constructed pair):\n";
    print_container(vpsi1.cbegin(), vpsi1.cend());

// use make_pair
    ifs.clear();
    ifs.seekg(0, ifs.beg);
    vector<pair<string,int>> vpsi2;
    while( ifs >> s >> i )
        vpsi2.push_back(make_pair(s, i));
    
    cout << "\n\nvpsi2 (using make_pair):\n";
    print_container(vpsi2.cbegin(), vpsi2.cend());

// use emplace_back
    ifs.clear();
    ifs.seekg(0, ifs.beg);
    vector<pair<string,int>> vpsi3;
    while( ifs >> s >> i )
        vpsi3.emplace_back(s, i);
    
    cout << "\n\nvpsi3 (using emplace_back):\n";
    print_container(vpsi3.cbegin(), vpsi3.cend());

// use an input operator defined for pair<string,int>
    ifs.clear();
    ifs.seekg(0, ifs.beg);
    vector<pair<string,int>> vpsi4;
    for( pair<string,int> p; ifs >> p; )
        vpsi4.push_back(std::move(p));
    
    cout << "\n\nvpsi4 using a custom input operator:\n";
    print_container(vpsi4.cbegin(), vpsi4.cend());
}

template<typename Iter>
void print_container(Iter begin, Iter end)
{
    while( begin != end ){
        cout << *begin;
        if( ++begin != end )
            cout << ", ";
    }
}

std::ostream& operator<<(std::ostream& os, const pair<string,int>& p)
{
    return os << "(" << p.first << ", " << p.second << ")";
}

std::istream& operator>>(std::istream& is, pair<string,int>& p)
{
    string s;
    int i;
    if( is >> s >> i ){
        p.first = s;
        p.second = i;
    }

    return is;
}
