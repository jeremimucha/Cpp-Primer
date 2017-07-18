// Chapter 15 -- Object oriented programming. Basket class.
#ifndef BASKET_H_
#define BASKET_H_

#include <iostream>
#include <memory>
#include <set>
#include "quote.h"


class Basket
{
public:
// Basket uses synthesized default constructor and copy-control members

// The following version of add_item would expose the user to memory allocation
// via the use of new or make_shared.
    // void add_item(const std::shared_ptr<Quote>& sale)
    //     { items.insert(sale); }

// We can handle memory allocation within the class, so that the user doesn't
// have to. This requires the Quote class hirerarchy to have a virtual member
// that dynamically returns the a pointer of appropriate type
// to a copy of itself. We defined a virtual Quote::clone() member for this purpose
    void add_item(const Quote& sale)    // copy the given object
        { items.insert(std::shared_ptr<Quote>(sale.clone()));
          std::cout << "add_item(const Quote&)" << std::endl; }
    void add_item(Quote&& sale)         // move the given object
        { items.insert(std::shared_ptr<Quote>(std::move(sale).clone())); 
          std::cout << "add_item(Quote&&)" << std::endl; }

    // prints the total price for each book and the overall total
    // for all items in th basket
    double total_receipt(std::ostream&) const;
private:
    // function to compare shared_ptrs needed by the multiset member
    static bool compare(const std::shared_ptr<Quote>& lhs,
                        const std::shared_ptr<Quote>& rhs)
        { return lhs->isbn() < rhs->isbn(); }
    // multiset to hold multiple quotes, ordered by the compare member
    // decltype(compare)* == bool(*)(const std::shared_ptr<Quote>&,const std::shared_ptr<Quote>&)
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{compare};
};



#endif /* BASKET_H_ */
