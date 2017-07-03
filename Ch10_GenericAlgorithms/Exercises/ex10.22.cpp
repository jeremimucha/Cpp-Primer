// ex10.22.cpp
/*Rewrite the program to count words of size 6 or less
using functions in place of the lambdas.*/
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <functional>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;
using std::bind;
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
using std::placeholders::_4;


bool check_size(const string& s, string::size_type sz);
std::ostream& print(std::ostream& os, const string& s, char ch);


int main()
{
    vector<string> words{"here", "are", "some", "words", "of", "various", "length",
                         "foo", "bar", "foobar"};
    cout << "words: ";
    // std::bind - binds arguments according to the args passed to bind
    // it returns a collable object with parameters bound to values
    // according to bind arguments. _1 is a placeholder - object returned by bind
    // will take the arguments according to the placeholder params.
    // 
    // std::ref - makes the given parameter into a reference
    // std::cref - constant reference
    std::for_each( words.cbegin(), words.cend(),
                   std::bind(print, std::ref(cout), _1, ' ') );   // can't copy ostream - convert to reference
    cout << endl;
    pair<vector<string>::const_iterator, vector<string>::const_iterator> short_long
        = std::minmax_element(words.cbegin(), words.cend(),
            [](const string& a, const string& b)
              { return a.size() < b.size(); });
    for( string::size_type len = short_long.first->size();
         len <= short_long.second->size()+1;
         ++len ){
             vector<string>::size_type cnt =
                std::count_if(words.cbegin(), words.cend(),
                              std::bind(check_size, _1, len) );
            cout << "Number of words with size < " << len << ": " << cnt
                 << endl;
         }
}


bool check_size(const string& s, string::size_type sz)
{
    return s.size() < sz;
}

std::ostream& print(std::ostream& os, const string& s, char ch)
{
    return os << s << ch;
}
