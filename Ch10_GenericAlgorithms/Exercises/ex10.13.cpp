// ex10.13.cpp
/*The library defines an algorithm named  partition that
takes a predicate and partitions the container so that values for which the
predicate is  true appear in the first part and those for which the predicate
is  false appear in the second part. The algorithm returns an iterator just
past the last element for which the predicate returned  true . Write a
function that takes a  string and returns a  bool indicating whether the
string has five characters or more. Use that function to partition  words .
Print the elements that have five or more characters.*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using std::cout;
using std::endl;
using std::vector;
using std::string;


class shorterThan
{
    size_t x;
public:
    explicit shorterThan(size_t val)
        : x(val) { }
    bool operator()(const string& s)
        { return s.size() >= x; }
};


int main()
{
    vector<string> words{"a", "b", "one", "two", "three", "four", "five",
                         "12345", "letters", "foobar"};
    cout << "words before partition:\n\t";
    for(const auto& w : words) cout << w << " ";
    cout << endl;
    vector<string>::iterator end_part =
        std::partition(words.begin(), words.end(), shorterThan(5));
    cout << "\nwords after partition:\n\t";
    cout << "pred == true: ";
    for(auto it=words.cbegin(); it!=end_part;){
        cout << *it++ << " ";
    }
    cout << "\n\tpred == false: ";
    for(auto it=end_part; it!=words.cend();)
        cout << *it++ << " ";
    
}
