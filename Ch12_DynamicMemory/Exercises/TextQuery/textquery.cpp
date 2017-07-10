#include "textquery.h"
#include <istream>
#include <sstream>
using std::endl;
using std::ostream;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;
using std::map;
using std::set;
using std::shared_ptr;
using std::make_shared;

// read the input file and build the map of lines to line numbers
TextQuery::TextQuery(ifstream& is)
    : file(make_shared<vector<string>>())
{
    string text;
    while( getline(is, text) ){
        file->push_back(text);
        int n = file->size() - 1;
        istringstream line(text);
        string word;
        while(line >> word){
            // if word isn't already in wm, subscripting adds a new entry
            shared_ptr<set<line_no>>& lines = wm[word];     // lines is ashared_ptr
            if(!lines)
                lines.reset(new set<line_no>);
            lines->insert(n);
        }
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
