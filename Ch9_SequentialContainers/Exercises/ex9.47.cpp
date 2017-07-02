// ex9.47.cpp
/*Write a program that finds each numeric character and
then each alphabetic character in the  string "ab2c3d7R4E6" . Write two
versions of the program. The first should use  find_first_of , and the
second  find_first_not_of */
#include <iostream>
#include <string>
using std::string;
using std::cout;


void print_num_pos(const string& s);
void print_alpha_pos(const string& s);
void print_nonalpha_pos(const string& s);
void print_nondigit_pos(const string& s);


int main()
{
    string s = "ab2c3d7R4E6";

    cout << "the string: " << s << "\n";
    cout << "numbers using print_num_pos:\n";
    print_num_pos(s);
    cout << "\nalphabetics using print_alpha_pos:\n";
    print_alpha_pos(s);
    cout << "\nnondigits using print_nondigit_pos:\n";
    print_nondigit_pos(s);
    cout << "\nnonalphabetics using print_nonalpha_pos:\n";
    print_nonalpha_pos(s);

    cout << "\n\nDone.\n";
    return 0;
}


void print_num_pos(const string& s)
{
    static const string numbers{"0123456789"};
    string::size_type pos = 0;
    while( (pos = s.find_first_of(numbers, pos)) != string::npos ){
        cout << "number " << s[pos] << " at position " << pos << "\n";
        ++pos;
    }
}

void print_alpha_pos(const string& s)
{
    static const string letters{"abcdefghijklmnoprstuwvxyzABCDEFGHIJKLMNOPRSTUWVXYZ"};
    string::size_type pos = 0;
    while( (pos =s.find_first_of(letters, pos)) != string::npos ){
        cout << "letter " << s[pos] << " at position " << pos << "\n";
        ++pos;
    }
}

void print_nonalpha_pos(const string& s)
{
    static const string letters{"abcdefghijklmnoprstuwvxyzABCDEFGHIJKLMNOPRSTUWVXYZ"};
    string::size_type pos = 0;
    while ( (pos = s.find_first_not_of(letters, pos)) != string::npos ){
        cout << "non-letter " << s[pos] << " at position " << pos << "\n";
        ++pos;
    }
}

void print_nondigit_pos(const string& s)
{
    static const string numbers{"0123456789"};
    string::size_type pos = 0;
    while ( (pos = s.find_first_not_of(numbers, pos)) != string::npos ){
        cout << "non-digit " << s[pos] << " at position " << pos << "\n";
        ++pos;
    }
}
