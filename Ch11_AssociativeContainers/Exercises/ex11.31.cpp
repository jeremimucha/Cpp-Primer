// ex11.31
/*Write a program that defines a  multimap of authors and
their works. Use  find to find an element in the  multimap and  erase that
element. Be sure your program works correctly if the element you look for
is not in the  map .*/
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>
using std::cout;
using std::endl;
using std::string;
using std::multimap;
using std::pair;
using std::to_string;

int main()
{
    multimap<string,string> authors;
    for(int i=1; i<4; ++i){
        for(int j=1; j<5; ++j)
            authors.insert({"Author"+to_string(i),"Title"+to_string(j)});
    }
    cout << "authors:\n";
    for(auto iter=authors.cbegin(); iter!=authors.cend(); ++iter){
        cout << "(" << iter->first <<", " << iter->second << ")\n";
    }
    multimap<string,string>::size_type count = authors.count("Author2");
    multimap<string,string>::const_iterator iter = authors.find("Author2");
    cout << "Entries for 'Author2':\n";
    if(count){
        while(count){
            cout << iter->second << ", ";
            --count;
            ++iter;
        }
    }
    else
        cout << "\b None.";

    count = authors.count("Author4");
    iter = authors.find("Author4");
    cout << "\nEntries for 'Author4':\n";
    if(count){
        while(count){
            cout << iter->second << ", ";
            --count;
            ++iter;
        }
    }
    else
        cout << "\b None.";
}
