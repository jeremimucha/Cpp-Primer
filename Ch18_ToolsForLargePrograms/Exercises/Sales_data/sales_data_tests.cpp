#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "Sales_data.h"
using std::cout;
using std::endl;
using std::unordered_map;
using std::unordered_set;


int main()
{
    Sales_data s1("1234", 11, 4.2);
    Sales_data s2("5432", 9, 3.14);

    try{
        s1 += s2;
    }
    catch(isbn_mismatch& e){
        std::cerr << "Handling the exception:\n";
        std::cerr << e.what() << ": left(" << e.left << "), right(" << e.right << ")";
    }
    std::cerr << "\nThe next exception won't be handled\n";
    s1 += s2;
}
