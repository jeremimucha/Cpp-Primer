#include "quote.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;


double Bulk_quote::net_price(std::size_t n) const
{
    if(n >= quantity)
        return n * (1 - discount) * price;
    else
        return n * price;
}

double Limited_quote::net_price(std::size_t n) const
{
    if(n <= quantity)
        return (price * n * (1-discount));
    else
        return price * (quantity * (1-discount) + (n-quantity));
}

void Quote::debug() const
{
    cout << "bookNo: " << bookNo << "\n"
         << "price: " << price << endl;
}

void Bulk_quote::debug() const
{
    Quote::debug();
    cout << "quantity: " << quantity << "\n"
            "discount: " << discount << endl;
}

void Limited_quote::debug() const
{
    Quote::debug();
    cout << "quantity: " << quantity << "\n"
         << "discount: " << discount << endl;
}