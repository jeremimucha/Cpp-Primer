// ex10.9.cpp
/*Implement your own version of  elimDups . Test your
program by printing the  vector after you read the input, after the call to
unique , and after the call to  erase .*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
using std::cout;
using std::endl;
using std::vector;
using std::string;


void elimDups(vector<string>& words);


int main()
{
    vector<string> vs{"foo", "bar", "test", "vector", "with", "foo",
                      "duplicate", "bar", "words"};
    elimDups(vs);
    
}


void elimDups(vector<string>& words)
{
    std::cout << "words before sort:\n\t";
    for(const auto& w : words) std::cout << w << " ";
    // sort the vector alphabetically
    std::sort(words.begin(), words.end());
    std::cout << "\nwords after sort:\n\t";
    for(const auto& w : words) std::cout << w << " ";
    // use unique to rearange the vector - put unique elems at the front
    auto end_unique = std::unique(words.begin(), words.end());
    std::cout << "\nwords after unique:\n\t";
    for(const auto& w : words) std::cout << w << " ";
    // erase uses a vector operation to remove the elements
    // past the unique ones
    words.erase(end_unique, words.end());
    std::cout << "\nwords afer erase:\n\t";
    for(const auto& w : words) std::cout << w << " ";
}