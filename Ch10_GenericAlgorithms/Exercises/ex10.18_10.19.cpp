// ex10.18_10.19 -- exercises 10.18 and 10.19
/*10.18: Rewrite  biggies to use  partition instead of  find_if . We
described the  partition algorithm in exercise 10.13 in § 10.3.1 (p. 387).
10.19: Rewrite the previous exercise to use  stable_partition ,
which like  stable_sort maintains the original element order in the
paritioned sequence.*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using std::cout;
using std::endl;
using std::vector;
using std::string;


void elimDups(vector<string>& words);
void biggies_partition(vector<string>& words, vector<string>::size_type sz);
void biggies_stable_partition(vector<string>& words, vector<string>::size_type sz);


int main()
{
    vector<string> words{"a", "b", "one", "two", "three", "four", "five",
                        "12345", "letters", "foobar"};
    cout << "using biggies_partition:\n";
    biggies_partition(words, 5);
    cout << "\n\nusing biggies_stable_partition:\n";
    biggies_stable_partition(words, 5);
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

void biggies_partition(vector<string>& words, vector<string>::size_type sz)
{
    elimDups(words);    // sort alphabetically and remove duplicates
    // sorty by size, maintain alphabetical order for words of the same size
    std::stable_sort(words.begin(), words.end(),
                     [](const string& a, const string& b)
                       { return a.size() < b.size(); });
    // get an interator to the first elem of size() >= sz;
    auto wc = std::partition(words.begin(), words.end(),
                            [sz](const string& s){ return s.size() < sz; });
    // compute teh number of elems with size >= sz
    vector<string>::size_type count = words.end() - wc;
    cout << "\n" << count << " " << "word(s)"
         << " of length " << sz << " or longer" << endl;
    // print words of the given size or longer
    std::for_each(wc, words.end(),
             [](const string& s){ cout << s << " "; });
    cout << endl;
}

void biggies_stable_partition(vector<string>& words, vector<string>::size_type sz)
{
    elimDups(words);
    auto wc = std::stable_partition(words.begin(), words.end(),
                         [sz](const string& s){ return s.size() < sz; });
    auto count = words.end() - wc;
    cout << "\n" << count << " " << "word(s)"
         << " of length " << sz << " or longer" << endl;
    // print words of the given size or longer
    std::for_each(wc, words.end(),
             [](const string& s){ cout << s << " "; });
    cout << endl;
}
