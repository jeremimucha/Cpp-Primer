// Chapter 15 -- Object Oriented Programming
#ifndef QUOTE_H_
#define QUOTE_H_

#include <iostream>
#include <string>
#include <memory>
#include <utility>


class Quote
{
public:
    Quote() = default;      // memberwise default initialize
    Quote(const std::string& book, double sales_price)
        : bookNo(book), price(sales_price)
        { }
    
// copy control
// Base classes don't have synthesized move constructors
// they need to be defined, which means copy ctors need to be defined aswell
    Quote(const Quote&) = default;      // memberwise copy
    Quote(Quote&&) = default;           // memberwise move
    Quote& operator=(const Quote&) = default;   // copy assign
    Quote& operator=(Quote&&) = default;        // move assign
    virtual ~Quote() = default; // dynamic binding for the dtor

// virtual function to return a dynamically allocated copy of itself
// these members use reference qualifiers
    virtual Quote* clone() const &
        { std::cout << "Quote::clone() const &" << std::endl;
            return new Quote(*this); }
    virtual Quote* clone() &&
        { std::cout << "Quote::clone() &&" << std::endl;
            return new Quote(std::move(*this)); }

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
    void do_debug() const;
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
    Disc_quote(const Disc_quote&) = default;
    Disc_quote(Disc_quote&&) = default;
    Disc_quote& operator=(const Disc_quote&) = default;
    Disc_quote& operator=(Disc_quote&&) = default;
    virtual ~Disc_quote() = default;
    // pure virtual function
    virtual double net_price(std::size_t) const override = 0;

protected:
    void do_debug() const;
    std::size_t quantity = 0;   // purchase size for the discount to apply
    double discount = 0.0;
};


// the discount kicks in when a specified number of copies of the same book are sold
class Bulk_quote : public Disc_quote
{
public:
    Bulk_quote() = default;
   
// inherit constructors with the using declaration
    using Disc_quote::Disc_quote;
    // Bulk_quote(const std::string& book, double sales_price,
    //            std::size_t qty, double disc)
    //     : Disc_quote(book, sales_price, qty, disc)
    //     { }

// copy and move constructors arent inherited via the using declaration
    Bulk_quote(const Bulk_quote&) = default;
    Bulk_quote(Bulk_quote&&) = default;
    Bulk_quote& operator=(const Bulk_quote&) = default;
    Bulk_quote& operator=(Bulk_quote&&) = default;

// virtual function to return a dynamically allocated copy of itself
    virtual Bulk_quote* clone() const &
        { std::cout << "Bulk_quote::clone() const &" << std::endl;
            return new Bulk_quote(*this); }
    virtual Bulk_quote* clone() &&
        { std::cout << "Bulk_quote::clone() &&" << std::endl;
            return new Bulk_quote(std::move(*this)); }

    ~Bulk_quote() = default;
    // overrides the base version in order to implement the bulk purchase discount policy
    virtual double net_price(std::size_t n) const override;
    virtual void debug() const override;
protected:
    void do_debug() const;
};

class Limited_quote : public Disc_quote
{
public:
    Limited_quote() = default;
    using Disc_quote::Disc_quote;

    Limited_quote(const Limited_quote&) = default;
    Limited_quote(Limited_quote&&) = default;
    Limited_quote& operator=(const Limited_quote&) = default;
    Limited_quote& operator=(Limited_quote&&) = default;

// virtual function to return a dynamically allocated copy of itself
    virtual Limited_quote* clone() const &
        { std::cout << "Limited_quote::clone() const &" << std::endl;
            return new Limited_quote(*this); }
    virtual Limited_quote* clone() &&
        { std::cout << "Limited_quote::clone() &&" << std::endl;
            return new Limited_quote(std::move(*this)); }

    ~Limited_quote() = default;
    virtual double net_price(std::size_t n) const override;
    virtual void debug() const override;
protected:
    void do_debug() const;
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


double print_total(std::ostream& os, const Quote& item, std::size_t n);


#endif /* QUOTE_H_ */
