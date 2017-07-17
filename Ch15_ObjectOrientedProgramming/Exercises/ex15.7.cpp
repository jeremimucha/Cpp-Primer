/* Exercise 15.7: Define a class that implements a limited discount strategy,
which applies a discount to books purchased up to a given limit. If the
number of copies exceeds that limit, the normal price applies to those
purchased beyond the limit. */
#include <iostream>
#include <string>


class Quote
{
public:
    Quote() = default;
    Quote(const std::string& book, double sales_price)
        : bookNo(book), price(sales_price)
        { }
    std::string isbn() const
        { return bookNo; }
    // returns the total sales price for the specified number of items
    // derived classes will override and apply different discount algorithms
    virtual double net_price(std::size_t n) const
        { return n * price; }
    virtual ~Quote() = default; // dynamic binding for the dtor

private:
    std::string bookNo;     // ISBN number of this item
protected:
    double price = 0.0;     // normal, undiscounted price
};


class Limited_quote : public Quote
{
public:
    Limited_quote() = default;
    Limited_quote(const std::string& book, double sales_price
                 ,std::size_t limit, double dsct)
        : Quote(book, sales_price)
        , max_qty(limit)
        , discount(dsct)
        { }
    ~Limited_quote() = default;
    double net_price(std::size_t n) const override;
private:
    std::size_t max_qty = 0;
    double discount = 0.0;
};


double Limited_quote::net_price(std::size_t n) const
{
    if(n <= max_qty)
        return (price * n * (1-discount));
    else
        return price * (max_qty * (1-discount) + (n-max_qty));
}


double print_total(std::ostream& os, const Quote& item, size_t n);


int main()
{
    Quote q("quote", 3.14);
    Limited_quote lq("Limited_quote", 3.14, 5, 0.1);
    print_total(std::cout, q, 11);
    std::cout << std::endl;
    print_total(std::cout, lq, 11);
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
