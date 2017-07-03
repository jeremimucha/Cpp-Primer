// ex10.33.cpp
/*Write a program that takes the names of an input file
and two output files. The input file should hold integers. Using an
istream_iterator read the input file. Using  ostream_iterator s, write the odd
numbers into the first output file. Each value should be followed by a
space. Write the even numbers into the second file. Each of these values
should be placed on a separate line.*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cstdlib>
using std::vector;
using std::istream_iterator;
using std::ostream_iterator;
using std::cin; using std::cout;


int main(int argc, char* argv[])
{
    if(argc != 4){
        cout << "Usage: " << argv[0] << "infile outfile1 outfile2\n";
        exit(EXIT_FAILURE);
    }
    std::ifstream ifs{argv[1]};
    if(!ifs.is_open()){
        cout << "Failed to open the file " << argv[1];
        exit(EXIT_FAILURE);
    }

    vector<int> numbers;
    std::copy(istream_iterator<int>(ifs), istream_iterator<int>(),
                std::back_inserter(numbers));
    std::sort(numbers.begin(), numbers.end());
    // partition - odd:even
    vector<int>::const_iterator splitpoint = 
        std::stable_partition(numbers.begin(), numbers.end(), [](int i){return i%2!=0;});
    
    std::ofstream ofs;
    ofs.open(argv[2], std::ios_base::app);
    std::unique_copy(numbers.cbegin(), splitpoint,
        std::ostream_iterator<int>(ofs, " "));
    ofs.clear();
    ofs.close();
    ofs.open(argv[3], std::ios_base::app);
    std::unique_copy(splitpoint, numbers.cend(),
        std::ostream_iterator<int>(ofs, "\n"));
}
