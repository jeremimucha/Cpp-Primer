// exs.8.2.1 -- Chapter 8 exercise section 8.2.1
/*Exercise 8.4: Write a function to open a file for input and read its
contents into a  vector of  string s, storing each line as a separate element
in the  vector.
Exercise 8.5: Rewrite the previous program to store each word in a
separate element.*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>      // for EXIT_FAILURE
#include <utility>



int main(int argc, char* argv[])
{
    if(argc<2){
        std::cerr << "Usage: " << argv[0] << " input_file\n";
        exit(EXIT_FAILURE);
    }

    std::ifstream infile(argv[1]);
    if(!infile.is_open()){
        std::cerr << "Failed to open the input file " << argv[1] << "\n";
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> lines;
    std::string temp;
    while(std::getline(infile, temp))
        lines.push_back(std::move(temp));
    infile.clear();
    infile.seekg(0, infile.beg);

    temp.clear();
    std::vector<std::string> words;
    while(infile >> temp)
        words.push_back(std::move(temp));

    std::cout << "Lines:\n";
    for(auto it=lines.cbegin(); it!=lines.cend(); ++it)
        std::cout << *it << "\n";

    std::cout << "\nWords:\n";
    for(const auto& word : words)
        std::cout << word << "\n";

    std::cout << "\nDone.\n";
    return 0;
}
