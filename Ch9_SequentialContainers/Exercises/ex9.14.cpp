// ex9.14 -- Chapter 9
/*Write a program to assign the elements from a  list of
char* pointers to C-style character strings to a  vector of  string s.*/
#include <iostream>
#include <vector>
#include <list>
#include <string>


template<typename Iter>
void print_container(Iter begin, Iter end);


int main()
{
    std::list<const char*> lcs{"list", "of", "const char*", "C-strings", "foo", "bar"};
    std::vector<std::string> vs{"original", "vs", "contents"};
    std::cout << "Before assignment.\n";
    std::cout << "lcs:  ";
    print_container(lcs.cbegin(), lcs.cend());
    std::cout << "\nvs:  ";
    print_container(vs.cbegin(), vs.cend());

    vs.assign(lcs.cbegin(), lcs.cend());
    std::cout << "\nAfter vs.assign(lcs.cbegin(), lcs.cend()).\n";
    std::cout << "lcs:  ";
    print_container(lcs.cbegin(), lcs.cend());
    std::cout << "\nvs:  ";
    print_container(vs.cbegin(), vs.cend());
}


template<typename Iter>
void print_container(Iter begin, Iter end)
{
    while( begin != end ){
        std::cout << *begin++;
        if( begin != end )
            std::cout << ", ";
    }
}
