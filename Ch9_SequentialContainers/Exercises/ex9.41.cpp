// ex9.41.cpp
/*Write a program that initializes a  string from a vector<char>.*/
#include <iostream>
#include <vector>
#include <string>



int main()
{
    using std::vector;
    using std::string;

    vector<char> vc{'f', 'o', 'o', 'b', 'a', 'r'};
    std::cout << "vc: ";
    for(auto it=vc.cbegin(); it!=vc.cend();){
        std::cout << *it++ << " ";
    }
    std::cout << "\n";
    string s(&vc[0], vc.size());
    std::cout << "str initialized with vc: " << s;

    string s2(vc.begin(), vc.end());
    std::cout << "\nanother string: " << s2;
    return 0;
}
