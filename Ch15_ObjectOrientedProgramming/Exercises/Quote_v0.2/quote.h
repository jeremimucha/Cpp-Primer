// Chapter 15 -- Object Oriented Programming
#ifndef QUOTE_H_
#define QUOTE_H_

#include <iostream>
#include <string>


class Quote
{
public:
    Quote() = default;
    Quote(const std::string& book, double sales_price)
        : bookNo(book), price(sales_price)
        { }
    virtual ~Quote() = default; // dynamic binding for the dtor

    std::string isbn() const
        { return bookNo; }
    // returns the total sales price for the specified number of items
    // derived classes will override and apply different discount algorithms
    virtual double net_price(std::size_t n) const
        { return n * price; }
    // prints all the members
    virtual void debug() const;

private:
    std::string bookNo;     // ISBN number of this item
protected:
    double price = 0.0;     // normal, undiscounted price
};


class Disc_quote : public Quote
{
public:
    Disc_quote() = default;
    Disc_quote(const std::string& book, double price
              ,std::size_t qty, double disc)
        : Quote(book, price)
        , quantity(qty)
        , discount(disc)
        { }
    virtual ~Disc_quote() = default;
    // pure virtual function
    virtual double net_price(std::size_t) const override = 0;

protected:
    std::size_t quantity = 0;   // purchase size for the discount to apply
    double discount = 0.0;
};


// the discount kicks in when a specified number of copies of the same book are sold
class Bulk_quote : public Disc_quote
{
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string& book, double sales_price,
               std::size_t qty, double disc)
        : Disc_quote(book, sales_price, qty, disc)
        { }
    ~Bulk_quote() = default;
    // overrides the base version in order to implement the bulk purchase discount policy
    virtual double net_price(std::size_t n) const override;
    virtual void debug() const override;
};

class Limited_quote : public Disc_quote
{
public:
    Limited_quote() = default;
    Limited_quote(const std::string& book, double sales_price
        , std::size_t qty, double disc)
        : Disc_quote(book, sales_price, qty, disc)
        { }
    ~Limited_quote() = default;
    virtual double net_price(std::size_t n) const override;
    virtual void debug() const override;
};


inline double Bulk_quote::net_price(std::size_t n) const
{
    if(n >= quantity)
        return n * (1 - discount) * price;
    else
        return n * price;
}

inline double Limited_quote::net_price(std::size_t n) const
{
    if(n <= quantity)
        return (price * n * (1-discount));
    else
        return price * (quantity * (1-discount) + (n-quantity));
}


#endif /* QUOTE_H_ */
