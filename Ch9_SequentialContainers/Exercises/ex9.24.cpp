// ex9.24.cpp
/*Write a program that fetches the first element in a  vector
using  at , the subscript operator,  front , and  begin . Test your program on
an empty  vector .*/
#include <iostream>
#include <vector>
#include <stdexcept>


int main()
{
    std::vector<int> vi{1,2,3,4,5,6,7,8,9,10};
    std::vector<int> vempty{};

    std::cout << "Accesing non-empty vector:\n";
    std::cout << vi.at(0) << "\n";
    std::cout << vi[0] << "\n";
    std::cout << vi.front() << "\n";
    std::cout << *vi.begin() << "\n";

    std::cout << "\nAccessing an empty vector:\n";
    try{
        std::cout << vempty.at(0) << "\n";
    }catch(std::exception ex){
        std::cerr << "Exception caught after calling vempty.at(0)\n";
        std::cerr << ex.what();
    }
    std::cout << vempty[0] << "\n";
    std::cout << vempty.front() << "\n";
    std::cout << *--vempty.begin() << "\n";
}
