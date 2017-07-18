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


double print_total(std::ostream& os, const Quote& item, std::size_t n)
{
    // depending on the type of the object bound to the item parameter
    // calls either Quote::net_price or Bulk_quote::net_price
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()   // calls Quote::isbn
       << " # sold: " << n << " total due: " << ret << std::endl;
    return ret;
}
