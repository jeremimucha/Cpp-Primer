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

    std::string isbn() const
        { return bookNo; }
    // returns the total sales price for the specified number of items
    // derived classes will override and apply different discount algorithms
    virtual double net_price(std::size_t n) const
        { return n * price; }
    // prints all the members
    virtual void debug() const;
    virtual ~Quote() = default; // dynamic binding for the dtor

private:
    std::string bookNo;     // ISBN number of this item
protected:
    double price = 0.0;     // normal, undiscounted price
};


class Bulk_quote : public Quote
{
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string& book, double sales_price)
        : Quote(book, sales_price)
        { }
    Bulk_quote(const std::string& book, double sales_price,
               std::size_t quantity, double dcount)
        : Quote(book, sales_price)
        , min_qty(quantity)
        , discount(dcount)
        { }
    ~Bulk_quote() = default;
    // overrides the base version in order to implement the bulk purchase
    // discount policy
    virtual double net_price(std::size_t n) const override;
    virtual void debug() const override;
private:
    std::size_t min_qty = 0;    // minimum purchase for discount to apply
    double discount = 0.0;      // fractional discount to apply
};

class Limited_quote : public Quote
{
public:
    Limited_quote() = default;
    Limited_quote(const std::string& book, double sales_price
        , std::size_t limit, double dsct)
        : Quote(book, sales_price)
        , max_qty(limit)
        , discount(dsct)
        { }
    ~Limited_quote() = default;
    virtual double net_price(std::size_t n) const override;
    virtual void debug() const override;
private:
    std::size_t max_qty = 0;
    double discount = 0.0;
};


inline double Bulk_quote::net_price(std::size_t n) const
{
    if(n >= min_qty)
        return n * (1 - discount) * price;
    else
        return n * price;
}

inline double Limited_quote::net_price(std::size_t n) const
{
    if(n <= max_qty)
        return (price * n * (1-discount));
    else
        return price * (max_qty * (1-discount) + (n-max_qty));
}


#endif /* QUOTE_H_ */
