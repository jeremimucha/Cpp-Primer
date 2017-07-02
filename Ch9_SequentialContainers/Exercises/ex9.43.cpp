// ex9.43.cpp
/*Write a function that takes three  string s,  s ,  oldVal , and
newVal . Using iterators, and the  insert and  erase functions replace all
instances of  oldVal that appear in  s by  newVal . Test your function by using
it to replace common abbreviations, such as “tho” by “though” and “thru”
by “through”.*/
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;


string& replace_all(string& str, const string& oldVal, const string& newVal);
template<typename IterA, typename IterB>
bool equal_range(IterA abegin, IterA aend, IterB bbegin, IterB bend);

int main()
{
    string s1{"test This is a test string test"};
    cout << "s1 before replace_all: " << s1 << "\n";
    replace_all(s1, "test", "TESTING");
    cout << "s1 after replace_all: " << s1 << "\n";

    cout << "\nDone.\n";
    return 0;
}

// Iterators, references and pointers to elements after the erasure
// point are invalidated
// inserting elements potentially invalidates all iterators, references
// and pointers
string& replace_all(string& str, const string& oldVal, const string& newVal)
{
    string::iterator subbeg = str.begin();
    while( subbeg + oldVal.size() != str.end() ){
        if( equal_range(subbeg, subbeg + oldVal.size(), oldVal.cbegin(), oldVal.cend() ) ){
            subbeg = str.erase(subbeg, subbeg + oldVal.size());  // subend invalid after the call
            str.insert(subbeg, newVal.begin(), newVal.end());    // subbeg needs to be refreshed
            subbeg += newVal.size();
        }
        else{
            ++subbeg;
        }
    }

    return str;
}

template<typename IterA, typename IterB>
bool equal_range(IterA abegin, IterA aend, IterB bbegin, IterB bend)
{
    while( abegin != aend && bbegin != bend ){
        if( *abegin++ != *bbegin++ )
            return false;
    }
    return true;
}
