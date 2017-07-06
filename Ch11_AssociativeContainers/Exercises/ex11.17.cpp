// ex11.17
/*ssuming  c is a  multiset of  string s and  v is a  vector of
string s, explain the following calls. Indicate whether each call is legal:
copy(v.begin(), v.end(), inserter(c, c.end()));
copy(v.begin(), v.end(), back_inserter(c));
copy(c.begin(), c.end(), inserter(v, v.end()));
copy(c.begin(), c.end(), back_inserter(v));*/
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <utility>
using std::cout; using std::endl;
using std::string;
using std::vector;
using std::set;
using std::multiset;
using std::inserter;


template<typename Iter>
void print_container(Iter begin, Iter end);


int main()
{
    vector<string> vs{"one", "one", "two", "two", "three", "four", "five",
        "three", "four", "five", "three", "four", "five", "four", "five", "five"};
    set<string> ss1;
    set<string> ss2;
    multiset<string> mss1;
    multiset<string> mss2;
    vector<string> vs2;

    cout << "vs: ";
    print_container(vs.cbegin(), vs.cend());
    cout << endl;

    std::copy(vs.cbegin(), vs.cend(), inserter(ss1, ss1.end()));
    cout << "ss1 (inserter(ss1, ss1.end()): ";
    print_container(ss1.cbegin(), ss1.cend());
    cout << endl;
    std::copy(vs.cbegin(), vs.cend(), inserter(ss2, ss2.begin()));
    cout << "ss2 (inserter(ss2, ss2.begin()): ";
    print_container(ss2.cbegin(), ss2.cend());
    cout << endl;
    std::copy(vs.cbegin(), vs.cend(), inserter(mss1, mss1.end()));
    cout << "mss1 (inserter(mss1, mss1.end()): ";
    print_container(mss1.cbegin(), mss1.cend());
    cout << endl;
    std::copy(vs.cbegin(), vs.cend(), inserter(mss2, mss2.begin()));
    cout << "mss2 (inserter(mss2, mss2.begin()): ";
    print_container(mss2.cbegin(), mss2.cend());
    cout << endl;
    std::copy(mss2.cbegin(), mss2.cend(), std::back_inserter(vs2));
    cout << "vs2 (back_inserter(vs2): ";
    print_container(vs2.cbegin(), vs2.cend());
    cout << endl;
}


template<typename Iter>
void print_container(Iter begin, Iter end)
{
    while( begin != end ){
        cout << *begin;
        if( ++begin != end )
            cout << ", ";
    }
}
