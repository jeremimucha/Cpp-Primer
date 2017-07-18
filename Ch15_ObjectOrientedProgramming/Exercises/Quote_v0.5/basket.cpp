#include "basket.h"
#include <iostream>
using std::ostream;
using std::multiset;
using std::shared_ptr;


double Basket::total_receipt(ostream& os) const
{
    double sum = 0.0;       // hold the running total
    // iter refers to the first element in a batch of elements with the same ISBN
    // upper bound returns an iterator to the element just past the end of that batch
    for(multiset<shared_ptr<Quote>>::const_iterator iter = items.cbegin();
            iter != items.cend();
            iter = items.upper_bound(*iter)){
        // we know there's at least one element with this key in the Basket
        // print the line item for this book
        sum += print_total(os, **iter, items.count(*iter));
    }
    os << "Total Sale: " << sum << std::endl;    // print the final overall total
    return sum;
}

