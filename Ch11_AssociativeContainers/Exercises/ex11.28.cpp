// ex11.28
/*Define and initialize a variable to hold the result of
calling  find on a  map from  string to  vector of  int .*/
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <utility>
using std::cout;
using std::vector;
using std::string;
using std::map;
using std::pair;


std::ostream& operator<<(std::ostream& os, const vector<int>& v);


int main()
{
    map<string,vector<int>> msvi{
                                 {"one",  {1,2,3,4,5}}
                                ,{"two",  {2,3,4,5,6}}
                                ,{"three",{3,4,5,6,7}}
                                };
    map<string,vector<int>>::const_iterator pos = msvi.find("two");
    if( pos != msvi.end() ){
        cout << "result of find 'two':"
             << "\n\tkey: " << pos->first
             << "\n\tmapped object values: " << pos->second
             << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const vector<int>& v)
{
    for(int i : v)
        os << i << ", ";
    return os;
}
