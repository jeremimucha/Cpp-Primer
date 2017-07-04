// exs11.2.2 -- exercise section 11.2.2
/*Exercise 11.9: Define a  map that associates words with a  list of line
numbers on which the word might occur.
Exercise 11.10: Could we define a  map from  vector<int>::iterator to  int ?
What about from  list<int>::iterator to  int ? In each case, if not, why not?
Exercise 11.11: Redefine  bookstore without using  decltype .*/
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <utility>
#include <functional>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::list;
using std::function;


class SalesData
{
public:
    SalesData(const string& title, const string& isbn, size_t sold)
        : title_(title), isbn_(isbn), sold_(sold) { }
    const string& isbn() const { return isbn_; }
private:
    string title_;
    string isbn_;
    size_t sold_;
};


bool compareIbn(const SalesData& lhs, const SalesData& rhs)
{
    return lhs.isbn() < rhs.isbn();
}


int main()
{
// ex 11.9
    cout << "ex 11.9:\n";
    map<string, list<int>> words{
         {"#include", {7,8,9,10,11}}
        ,{"const", {17, 27}}
        };
    for( const auto& word : words ){
        cout << word.first << " occurs on lines: ";
        for( int i : word.second )
            cout << i << ", ";
        cout << endl;
    }

// ex 11.10
    cout << "\n\nex 11.10:\n";
    vector<int> vi{1,2,3,4,5,6,7,8,9};
    // must provide a comparison function for vector<int>::iterator
    map<vector<int>::iterator, int,
        function<bool(vector<int>::iterator,vector<int>::iterator)>
       > map_itvi([](vector<int>::iterator a, vector<int>::iterator b)
                    { return b - a > 0;});
    for(vector<int>::iterator it=vi.begin(); it!=vi.end(); ++it){
        map_itvi[it] = *it + 10;
    }

    cout << "map< vector<int>::iterator, int >:\n";
    for(const auto& a : map_itvi){
        cout << "iter value: " << *a.first
             << "\n\tmapped to: " << a.second
             << std::endl;
    }

    list<int> li{1,2,3,4,5,6,7,8,9};
    // must provide a comparison function for list<int>::iterator
    // here we compare by value pointed to
    map<list<int>::iterator, int,
        function<bool(list<int>::iterator,list<int>::iterator)>
       > map_itli([](list<int>::iterator a, list<int>::iterator b)
                    { return *a < *b;});
    for( auto it=li.begin(); it!=li.end(); ++it){
        map_itli[it] = *it + 20;
    }

    cout << "\nmap< list<int>::iterator, int >:\n";
    for(const auto& a : map_itli){
        cout << "iter value: " << *a.first
             << "\n\tmapped to: " << a.second
             << std::endl;
    }
}
