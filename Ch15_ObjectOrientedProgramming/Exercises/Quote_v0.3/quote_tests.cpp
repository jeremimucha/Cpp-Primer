// Chapter 15 -- Object oriented programming
// minimal test code for the Quote and inheriting classes
#include <iostream>
#include <vector>
#include "quote.h"


// 
double print_total(std::ostream& os, const Quote& item, size_t n);


int main()
{
    Quote q("quote book", 3.14);
    Bulk_quote bq("bulk quote book", 3.14, 5, 0.2);
    Limited_quote lq("limited quote book", 3.14, 5, 0.2);
    print_total(std::cout, q, 12);
    print_total(std::cout, bq, 12);
    print_total(std::cout, lq, 12);

    // Illegal - Disc_quote is an abstract base class with pure virtual functions
    // Disc_quote dq = Disc_quote("disc_quote", 3.14, 5, 0.2);

// ex 15.11 debug function - display data members
    std::cout << "\nex 15.11 debug function - display data members:\n";
    Quote q1("quote 1", 3.14);
    Bulk_quote bq1("bulk quote 1", 3.14, 5, 0.2);
    Limited_quote lq1("liimted quote 1", 3.14, 5, 0.2);
    std::vector<Quote*> vq{&q1, &bq1, &lq1};
    for( Quote* p : vq)
        p->debug();
}


double print_total(std::ostream& os, const Quote& item, size_t n)
{
    // depending on the type of the object bound to the item parameter
    // calls either Quote::net_price or Bulk_quote::net_price
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()   // calls Quote::isbn
       << " # sold: " << n << " total due: " << ret << std::endl;
    return ret;
}
