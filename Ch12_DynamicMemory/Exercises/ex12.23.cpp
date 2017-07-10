// ex 12.23
/*Write a program to concatenate two string literals,
putting the result in a dynamically allocated array of  char . Write a program
to concatenate two library  string s that have the same value as the literals
used in the first program.*/
#include <iostream>
#include <string>
#include <cstring>
using std::cout;
using std::endl;
using std::strlen;
using std::strcpy;
using std::strcat;


int main()
{
// Using string literals and dynamically allocated array of char
    const char* s1 = "First String";
    const char* s2 = "Second String";
    cout << "Using string literals and dynamically allocated memory:\n";
    size_t lens1 = strlen(s1);
    size_t lens2 = strlen(s2);
    char* ss = new char[lens1 + lens2 + 1];
    strcpy(ss, s1);
    strcat(ss, s2);
    ss[lens1+lens2] = '\0';
    cout << "s1: " << s1 << "\n";
    cout << "s2: " << s2 << "\n";
    cout << "Concatenated strings: " << ss << "\n";

    delete[] ss;

// using library string
    cout << "\nUsing string:\n";
    std::string str1("First String");
    std::string str2("Second String");
    std::string str3 = str1 + str2;
    cout << "str1: " << str1 << "\n";
    cout << "str2: " << str2 << "\n";
    cout << "str3: " << str3 << "\n";
}
