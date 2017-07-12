#include "textquery.h"
#include "strvec.h"
#include <istream>
#include <sstream>
#include <utility>
using std::endl;
using std::ostream;
using std::ifstream;
using std::istringstream;
using std::string;
using std::map;
using std::set;
using std::shared_ptr;
using std::make_shared;
using std::pair;
using std::move;

// read the input file and build the map of lines to line numbers
TextQuery::TextQuery(ifstream& is)
    : file(make_shared<StrVec>())
{
    int n{0};
    for( string text; getline(is, text); ++n ){
        // file->push_back(text);
        istringstream line(text);
        string word;
        while(line >> word){
            // if word isn't already in wm, subscripting adds a new entry
            // shared_ptr<set<line_no>>& lines = wm[trim(word)];     // lines is ashared_ptr
            // if(!lines)
            //     lines.reset(new set<line_no>);
            // lines->insert(n);

            // or use insert instead
// insert returns a pair of <iterator, insertion-result>
// iterator points to the map's value_type with the given key
// insertion-result is true if the element was inserted
// and false if it already existed
// res.first gives us the iterator
// iterator points to the value_type, i.e. pair<string, shared_ptr<set<line_no>>>
// so res.first->second gives us the shared_ptr<set<line_no>>>
// it contains a nullptr right after insertion, so if the insertion was
// successful we need to allocate a set<line_no> object and reset the
// shared_ptr to point to it
// we then insert the current line number with res.first->second->insert(n);
            pair<map<string, shared_ptr<set<line_no>>>::iterator,
                 bool> res = 
                wm.insert({trim(word), shared_ptr<set<line_no>>()});
            if(res.second)
                res.first->second.reset(new set<line_no>);
            res.first->second->insert(n);
        }
        file->push_back(std::move(text));
    }
}


QueryResult TextQuery::query(const string& sought) const
{
    // we'll return a pointer to this set if we don't find sought
    static shared_ptr<set<line_no>> nodata(make_shared<set<line_no>>());
    // use find and not a subscript to avoid adding words to wm!
    auto loc = wm.find(sought);
    if( loc == wm.end() )
        return QueryResult(sought, nodata, file);   // not found
    else
        return QueryResult(sought, loc->second, file);
}

const char* TextQuery::whitespace{",.<>?/;:\'\"[{]}~`!@#$%^&*()"};
std::string& TextQuery::trim(string& str)
{
// find the index of first non-whitespace character
    string::size_type index = str.find_first_not_of(whitespace);
    str.erase(0, index);
// find the index of the last non-whitespace character
    index = str.find_last_not_of(whitespace);
    str.erase(index+1);
    return str;
}

ostream& print(ostream& os, const QueryResult& qr)
{
    // if the word was found, print the count and all occurrences
    os << qr.sought << " occurs " << qr.lines->size() << " "
       << "time(s)" << endl;
    // print each line in which the word appeared
    for( auto num : *qr.lines ) // for every element in the set
        // don't confound the user with text lines starting at 0
        os << "\t(line " << num + 1 << ") "
           << *(qr.file->begin() + num) << endl;
    return os;
}
