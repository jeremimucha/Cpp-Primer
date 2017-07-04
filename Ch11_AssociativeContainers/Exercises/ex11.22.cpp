// ex 11.22
/*Given a  map<string, vector<int>> , write the types used
as an argument and as the return value for the version of  insert that
inserts one element.*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
using std::cout;
using std::vector;
using std::string;
using std::map;
using std::pair;


std::ostream& operator<<(std::ostream& os, const vector<int>& v);


int main()
{
    map<string,vector<int>> msvi;
    pair<map<string,vector<int>>::const_iterator,bool> ret = 
    msvi.insert({"Test",{1,2,3,4,5}});
    cout.setf(std::ios_base::boolalpha);
    cout << "After first insert:\n\t"
         << "Was the element inserted? " << ret.second
         << "\n\tIterator's key: " << ret.first->first
         << "\n\tIterator's value: " << ret.first->second;

    ret = msvi.insert({"Test",{1,2,3,4,5}});
    cout << "\n\nAfter second insert:\n\t"
         << "Was the element inserted? " << ret.second
         << "\n\tIterator's key: " << ret.first->first
         << "\n\tIterator's value: " << ret.first->second;
}

std::ostream& operator<<(std::ostream& os, const vector<int>& v)
{
    for(auto it=v.cbegin();  it!=v.cend();){
        os << *it;
        if( ++it != v.cend() )
            os << ", ";
    }
    return os;
}