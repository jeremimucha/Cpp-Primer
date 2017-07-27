/* Exercise 17.4: Write and test your own version of the  findBook function. */
#include <iostream>
#include "./incl/sales_data.h"
#include <tuple>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::tuple;
using std::make_tuple;
using std::get;
using std::pair;
using std::equal_range;
using std::accumulate;


using matches = tuple<vector<Sales_data>::size_type,
                      vector<Sales_data>::const_iterator,
                      vector<Sales_data>::const_iterator>;


vector<matches> findBook(const vector<vector<Sales_data>>& files,
                         const string& book);


void reportResults(std::istream& in, std::ostream& os,
                   const vector<vector<Sales_data>>& files);


int main()
{
    vector<vector<Sales_data>> files
        {
            { {"Foo", 1, 1.1}, {"Bar", 2, 2.2}, {"Foobar", 3, 3.3} }
           ,{ {"Foo", 4, 4.4}, {"Book", 5, 5.5}, {"Nope", 6, 6.6} }
           ,{ {"Another", 7, 7.7}, {"More", 8, 8.8}, {"Foo", 9, 9.9}, {"Foobar", 10, 10.1} }
           ,{ {"Bla", 11, 11.11}, {"Foo", 12, 12.2} }
        };
    for(auto it = files.begin(); it != files.end(); ++it){
        std::sort(it->begin(), it->end(), compareIsbn);
    }
    reportResults(std::cin, cout, files);
}


vector<matches> findBook(const vector<vector<Sales_data>>& files,
                         const string& book)
{
    vector<matches> ret;        // empty
    // for each store find the range of matching books, if any
    for(vector<vector<Sales_data>>::const_iterator it = files.cbegin();
        it != files.cend(); ++it){
            // find the range of Sales_data that have the same ISBN
            pair<vector<Sales_data>::const_iterator,
                 vector<Sales_data>::const_iterator> found = equal_range(
                        it->cbegin(), it->cend(), book, compareIsbn);
            if(found.first != found.second) // the store sold this book
                // remember the index of this store and the matching range
                ret.push_back(make_tuple(it - files.cbegin(),
                                         found.first, found.second));
        }
    return ret; // empty if no matches;
}

void reportResults(std::istream& in, std::ostream& os,
                   const vector<vector<Sales_data>>& files)
{
    string s;   // book to look for
    while(cout << ">> " && in >> s){
        vector<matches> trans = findBook(files, s);  // stores that sold this book
        if(trans.empty()){
            cout << s << " not found in any stores" << endl;
            continue;
        }
        for(const auto& store : trans)  // for every store with a sale
            // get<n> returns the specified member from the tuple in store
            os << "store " << get<0>(store) << " sales: "
               << accumulate(get<1>(store), get<2>(store), Sales_data(s))
               << endl;
    }
}
