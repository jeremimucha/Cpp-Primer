// ex8.11.cpp -- Chapter 8
/*8.11: The program in this section defined its  istringstream
object inside the outer  while loop. What changes would you need to make
if  record were defined outside that loop? Rewrite the program, moving the
definition of  record outside the  while , and see whether you thought of all
the changes that are needed.*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>


struct PersonInfo
{
    std::string name;
    std::vector<std::string> phones;
};


std::ostream& operator<<(std::ostream& os, const PersonInfo& info);


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

    std::string line, word;
    std::vector<PersonInfo> people;
    std::istringstream record;
    while(std::getline(infile, line)){
        PersonInfo info;
        record.str(line);
        record >> info.name;
        while(record >> word)
            info.phones.push_back(std::move(word));
        record.clear();
        people.push_back(std::move(info));
    }

    std::cout << "People:\n";
    for(auto it=people.cbegin(); it!=people.cend(); ++it)
        std::cout << *it << "\n";

    std::cout << "\nDone.\n";
    return 0;
}


std::ostream& operator<<(std::ostream& os, const PersonInfo& info)
{
    os << "Name: " << info.name
       << "\n\tPhones: ";
    for(const auto& phone : info.phones)
        os << phone << " ";
    return os;
}
