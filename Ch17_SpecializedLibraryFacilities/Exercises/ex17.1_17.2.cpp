/* Exercise 17.1: Define a  tuple that holds three  int values and initialize the
members to  10, 20 , and  30 .
Exercise 17.2: Define a  tuple that holds a  string , a  vector<string> , and a
pair<string, int> . */
#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <utility>
using std::cout;
using std::endl;
using std::tuple;
using std::tuple_size;
using std::tuple_element;
using std::get;
using std::string;
using std::vector;
using std::pair;
using std::make_pair;


template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& vect);

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const pair<T1,T2>& p);


int main()
{
    tuple<int,int,int> v3i{10,20,30};
    tuple<string, vector<string>, pair<string,int>> tup{
        "str", vector<string>{"vector","of","strings", make_pair("str", 42)};
    cout << "v3i: " << get<0>(v3i) << ", " << get<1>(v3i) << ", " << get<2>(v3i);
    cout << endl;
    cout << "tup: " << get<0>(tup) << ", " << get<1>(tup) << ", " << get<2>(tup);
}


template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& vect)
{
    os << "{";
    for(typename vector<T>::const_iterator it = vect.cbegin();
        it != vect.cend(); ){
            os << *it;
            if(++it != vect.cend()) os << ", ";
        }
    return os << "}";
}

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const pair<T1,T2>& p)
{
    return os << "(" << p.first << ", " << p.second << ")";
}
