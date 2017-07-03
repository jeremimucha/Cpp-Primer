// ex10.20.cpp
/*The library defines an algorithm named  count_if . Like
find_if , this function takes a pair of iterators denoting an input range and
a predicate that it applies to each element in the given range.  count_if
returns a count of how often the predicate is true. Use  count_if to rewrite
the portion of our program that counted how many words are greater than
length 6.*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;


int main()
{
    vector<string> words{"here", "are", "some", "words", "of", "various", "length",
                         "foo", "bar", "foobar"};
    pair<vector<string>::const_iterator, vector<string>::const_iterator> short_long
        = std::minmax_element(words.begin(), words.end(),
                            [](const string& a, const string& b)
                               { return a.size() < b.size(); }
                             );
    for( string::size_type len=short_long.first->size();
         len <= short_long.second->size();
         ++len ){
             cout << "Number of words with size = " << len << ": ";
             cout << count_if(words.begin(), words.end(),
                              [len](const string& s){ return s.size() == len; }
                              );
            cout << endl;
         }
}
