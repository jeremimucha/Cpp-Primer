/* Exercise 15.30: Write your own version of the  Basket class and use it to
compute prices for the same transactions as you used in the previous
exercises.
*/
#include <iostream>
#include <vector>
#include <memory>
#include "quote.h"
#include "basket.h"
using std::cout;
using std::endl;
using std::vector;


int main()
{
    Quote q("Quote", 1.1);
    Bulk_quote bq("Bulk Quote", 2.2, 2, 0.2);
    Limited_quote lq("Limited Quote", 3.3, 1, 0.3);

    Basket basket;
    basket.add_item(q);
    basket.add_item(bq);
    basket.add_item(lq);
    basket.add_item(std::move(q));
    basket.add_item(std::move(bq));
    basket.add_item(std::move(lq));
    basket.add_item(Quote("Quote 2", 11.11));
    basket.add_item(Bulk_quote("Bulk Quote 2", 22.22, 2, 0.22));
    basket.add_item(Limited_quote("Limited Quote 2", 33.33, 1, 0.33));
    basket.add_item(Quote("Quote 2", 11.11));
    basket.add_item(Bulk_quote("Bulk Quote 2", 22.22, 2, 0.22));
    basket.add_item(Limited_quote("Limited Quote 2", 33.33, 1, 0.33));
    basket.add_item(Quote("Quote 2", 11.11));
    basket.add_item(Bulk_quote("Bulk Quote 2", 22.22, 2, 0.22));
    basket.add_item(Limited_quote("Limited Quote 2", 33.33, 1, 0.33));
    basket.add_item(Quote("Quote 2", 11.11));
    basket.add_item(Bulk_quote("Bulk Quote 2", 22.22, 2, 0.22));
    basket.add_item(Limited_quote("Limited Quote 2", 33.33, 1, 0.33));

    basket.total_receipt(cout);
}
