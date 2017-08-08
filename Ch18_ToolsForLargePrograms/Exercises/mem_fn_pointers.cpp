/* Exercise 19.18: Write a function that uses  count_if to count how many
empty  string s there are in a given  vector . 
Exercise 19.19: Write a function that takes a  vector<Sales_data> and
finds the first element whose average price is greater than some given
amount.*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include "./Sales_data/sales_data.h"
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::placeholders::_1;


vector<string>::size_type count_empty(const vector<string>&);

vector<Sales_data>::const_iterator find_greater(const vector<Sales_data>&, double price);

int main()
{

}


vector<string>::size_type count_empty(const vector<string>& v)
{
    return std::count_if(v.cbegin(), v.cend(),
        std::mem_fn(&string::empty));
// or
    // return std::count_if(v.cbegin(), v.cend(),
    //     std::bind(&string::empty, _1));
// or
    // return std::count_if(v.cbegin(), v.cend(),
    //     std::function<bool(const string&)>(&string::empty));
}

vector<Sales_data>::const_iterator find_greater(const vector<Sales_data>& v, double price)
{
    double (Sales_data::*pmf)() const = Sales_data::get_pavg_price();
    return std::find_if(v.cbegin(), v.cend(),
        [pmf, price](const Sales_data& sd) { return price < (sd.*pmf)(); });
}
