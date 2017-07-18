// Chapter 15 -- Object oriented programming
// minimal test code for the Quote and inheriting classes
#include <iostream>
#include <vector>
#include "quote.h"



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
