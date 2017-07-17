#include "quote.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;


void Quote::debug() const
{
    cout << "bookNo: " << bookNo << "\n"
         << "price: " << price << endl;
}

void Bulk_quote::debug() const
{
    Quote::debug();
    cout << "min_qty: " << min_qty << "\n"
            "discount: " << discount << endl;
}

void Limited_quote::debug() const
{
    Quote::debug();
    cout << "max_qt: " << max_qty << "\n"
         << "discount: " << discount << endl;
}
