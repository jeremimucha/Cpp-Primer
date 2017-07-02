// ex10.11.cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using std::string;
using std::vector;
using std::cout;
using std::endl;


bool isShorter(const string& s1, const string& s2);
void elimDups(vector<string>& words);


int main()
{
    vector<string> vs{"foo", "bar", "test", "vector", "with", "foo",
                      "duplicate", "bar", "words"};
    elimDups(vs);
    std::stable_sort(vs.begin(), vs.end(), isShorter);
    cout << "\nAfter stable_sort:\n\t";
    for(const auto& s : vs) cout << s << " ";

}


bool isShorter(const string& s1, const string& s2)
{
    return s1.size() < s2.size();
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
