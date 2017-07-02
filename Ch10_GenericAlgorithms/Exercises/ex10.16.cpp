// ex10.16.cpp
/*Write your own version of the  biggies function using lambdas.*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using std::string;
using std::vector;
using std::cout;
using std::endl;


void elimDups(vector<string>& words);
void biggies(vector<string>& words, vector<string>::size_type sz);


int main()
{
    vector<string> words{"a", "b", "one", "two", "three", "four", "five",
                        "12345", "letters", "foobar"};
    biggies(words, 5);
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

void biggies(vector<string>& words, vector<string>::size_type sz)
{
    elimDups(words);    // sort alphabetically and remove duplicates
    // sorty by size, maintain alphabetical order for words of the same size
    std::stable_sort(words.begin(), words.end(),
                     [](const string& a, const string& b)
                       { return a.size() < b.size(); });
    // get an interator to the first elem of size() >= sz;
    auto wc = std::find_if(words.begin(), words.end(),
                            [sz](const string& s)
                                { return s.size() >= sz; });
    // using partition
    // auto wc = std::partition(words.begin(), words.end(),
    //                         [sz](const string& s){ return s.size() < sz; });
    // compute teh number of elems with size >= sz
    vector<string>::size_type count = words.end() - wc;
    cout << "\n" << count << " " << "word(s)"
         << " of length " << sz << " or longer" << endl;
    // print words of the given size or longer
    std::for_each(wc, words.end(),
             [](const string& s){ cout << s << " "; });
    cout << endl;
}
