// exs8.3.1.cpp -- Chapter 8
/*8.10: Write a program to store each line from a file in a
vector<string> . Now use an  istringstream to read each element from the
vector a word at a time.*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
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
    
    std::cout << "Lines:\n";
    for(const auto& line : lines)
        std::cout << line << "\n";

    std::cout << "\nWords:\n";
    temp.clear();
    for(auto it=lines.cbegin(); it!=lines.cend(); ++it){
        std::istringstream iss(*it);
        while(iss >> temp)
            std::cout << temp << "\n";
    }

    infile.close();
    std::cout << "\nDone.\n";
    return 0;
}
