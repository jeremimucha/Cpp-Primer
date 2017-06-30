// ex9.18.cpp -- Chapter 9
/*Write a program to read a sequence of  string s from the
standard input into a  deque . Use iterators to write a loop to print the
elements in the  deque .
9.19: Rewrite the program from the previous exercise to use a
list . List the changes you needed to make. */
#include <iostream>
#include <string>
#include <deque>
#include <list>
#include <utility>


int main()
{
    using std::cin;
    using std::cout;
    using std::endl;

    std::cout << "Please enter a sequence of strings.\n";
    std::string temp;
    std::deque<std::string> dqstrings;
    std::list<std::string> lststrings;

    while(cin >> temp){
        dqstrings.push_back(temp);
        lststrings.push_back(std::move(temp));
        if(cin.peek() == '\n')
            break;
    }

    cout << "Elements in the deque:\n";
    for(std::deque<std::string>::const_iterator it = dqstrings.cbegin();
        it != dqstrings.cend();
       )
       {
            cout << *it;
            if(++it != dqstrings.cend())
                cout << ", ";
       }
    std::cout << "\n";

    std::cout << "\nDone.\n";
    return 0;
}
