#include "quote.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;

void Quote::do_debug() const
{
    cout << "bookNo: " << bookNo << "\n"
         << "price: " << price << endl;
}

void Disc_quote::do_debug() const
{
    cout << "quantity: " << quantity << "\n"
            "discount: " << discount << endl;
}

void Bulk_quote::do_debug() const
{ }

void Limited_quote::do_debug() const
{ }


void Quote::debug() const
{
    cout << "Quote::debug()\n";
    do_debug();
}


void Bulk_quote::debug() const
{
    cout << "Bulk_quote::debug()\n";
    Quote::do_debug();
    Disc_quote::do_debug();
}

void Limited_quote::debug() const
{
    cout << "Limited_quote::debug()\n";
    Quote::do_debug();
    Disc_quote::do_debug();
}
