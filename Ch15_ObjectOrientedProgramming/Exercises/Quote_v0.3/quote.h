/* Exercise 15.26: Define the  Quote and  Bulk_quote copy-control members to
do the same job as the synthesized versions. Give them and the other
constructors print statements that identify which function is running. Write
programs using these classes and predict what objects will be created and
destroyed. Compare your predictions with the output and continue
experimenting until your predictions are reliably correct. */
#include <iostream>
#include <string>
#include <utility>
using std::cout;
using std::endl;


class Quote
{
public:
    Quote()
        { cout << "Quote()" << " -> "; }
    Quote(const std::string& book, double sales_price)
        : bookNo(book), price(sales_price)
        { cout << "Quote(const string&, double)" << " -> "; }
    
    Quote(const Quote& q)
        : bookNo(q.bookNo), price(q.price)
        { cout << "Quote(const Quote&)" << " -> "; }
    Quote(Quote&& q)
        : bookNo(std::move(q.bookNo)), price(std::move(q.price))
        { cout << "Quoe(Quote&&)" << " -> "; }
    Quote& operator=(const Quote&);   // copy assign
    Quote& operator=(Quote&&);        // move assign
    virtual ~Quote()
        { cout << "~Quote()" << endl; }

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
    Disc_quote()
        { cout << "Disc_quote()" << " -> "; }
    Disc_quote(const std::string& book, double price
              ,std::size_t qty, double disc)
        : Quote(book, price)
        , quantity(qty)
        , discount(disc)
        { cout << "Disc_quote(const string&, double, size_t, double)" << " -> "; }
    Disc_quote(const Disc_quote& d)
        : Quote(d), quantity(d.quantity), discount(d.discount)
        { cout << "Disc_quote(const Disc_quote&)" << " -> "; }
    Disc_quote(Disc_quote&& d)
        : Quote(std::move(d)), quantity(std::move(d.quantity)),
          discount(std::move(d.discount))
        { cout << "Disc_quote(Disc_quote&&)" << " -> "; }
    Disc_quote& operator=(const Disc_quote&);
    Disc_quote& operator=(Disc_quote&&);
    virtual ~Disc_quote()
        { cout << "~Disc_quote()" << " -> "; }
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
    Bulk_quote()
        { cout << "Bulk_quote" << endl; }
    Bulk_quote(const std::string& book, double sales_price,
               std::size_t qty, double disc)
        : Disc_quote(book, sales_price, qty, disc)
        { cout << "Bulk_quote(const string&, double, size_t, double)" << endl; }
    Bulk_quote(const Bulk_quote& b)
        : Disc_quote(b)
        { cout << "Bulk_quote(const Bulk_quote)" << endl; }
    Bulk_quote(Bulk_quote&& b)
        : Disc_quote(std::move(b))
        { cout << "Bulk_quote(Bulk_quote&&)" << endl; }
    Bulk_quote& operator=(const Bulk_quote&);
    Bulk_quote& operator=(Bulk_quote&&);
    ~Bulk_quote()
        { cout << "~Bulk_quote()" << " -> "; }
    // overrides the base version in order to implement the bulk purchase discount policy
    virtual double net_price(std::size_t n) const override;
    virtual void debug() const override;
};

class Limited_quote : public Disc_quote
{
public:
    Limited_quote()
        { cout << "Limited_quote()" << endl; }
    
// using Disc_quote::Disc_quote;
// inherits constructors from Disc_quote, this does not include the
// copy and move constructors. The using declaration would generate
// code equivalent to the following (minus the cout...):
    Limited_quote(const std::string& book, double sales_price
        , std::size_t qty, double disc)
        : Disc_quote(book, sales_price, qty, disc)
        { cout << "Limited_quote(const string&, double, size_t, double)" << endl; }

    Limited_quote(const Limited_quote& lq)
        : Disc_quote(lq)
        { cout << "Limited_quote(const Limited_quote&)" << endl; }
    Limited_quote(Limited_quote&& lq)
        : Disc_quote(std::move(lq))
        { cout << "Limited_quote(Limited_quote&&)" << endl; }

    Limited_quote& operator=(const Limited_quote&);
    Limited_quote& operator=(const Limited_quote&&);
    
    ~Limited_quote()
        { cout << "~Limited_quote() -> "; }

    virtual double net_price(std::size_t n) const override;
    virtual void debug() const override;
};


inline Quote& Quote::operator=(const Quote& rhs)
{
    cout << "operator=(const Quote&) entry -> ";
    if(this == &rhs)
        return *this;
    bookNo = rhs.bookNo;
    price = rhs.price;
    cout << "operator=(const Quote&) exit -> ";
    return *this;
}
inline Quote& Quote::operator=(Quote&& rhs)
{
    cout << "operator=(Quote&&) entry -> ";
    if(this == &rhs)
        return *this;
    bookNo = std::move(rhs.bookNo);
    price = std::move(rhs.price);
    cout << "operator=(Quote&&) exit -> ";
    return *this;
}

inline Disc_quote& Disc_quote::operator=(const Disc_quote& rhs)
{
    cout << "operator=(const Disc_quote&) entry -> ";
    if(this != &rhs){
        Quote::operator=(rhs);
        quantity = rhs.quantity;
        discount = rhs.discount;
    }
    cout << "operator=(const Disc_quote&) exit -> ";
    return *this;
}
inline Disc_quote& Disc_quote::operator=(Disc_quote&& rhs)
{
    cout << "operator=(Disc_quote&&) entry -> ";
    if(this != &rhs){
        Quote::operator=(std::move(rhs));
        quantity = std::move(rhs.quantity);
        discount = std::move(rhs.discount);
    }
    cout << "operator=(Disc_quote&&) exit -> ";
    return *this;
}

inline Bulk_quote& Bulk_quote::operator=(const Bulk_quote& rhs)
{
    cout << "operator=(const Bulk_quote&) entry ->";
    if(this != &rhs){
        Disc_quote::operator=(rhs);
    }
    cout << "operator=(const Bulk_quote&) exit" << endl;
    return *this;
}
inline Bulk_quote& Bulk_quote::operator=(Bulk_quote&& rhs)
{
    cout << "operator=(Bulk_quote&&) entry -> ";
    if(this != &rhs){
        Disc_quote::operator=(std::move(rhs));
    }
    cout << "operator=(Bulk_quote&&) exit" << endl;
    return *this;
}

inline Limited_quote& Limited_quote::operator=(const Limited_quote& rhs)
{
    cout << "operator=(const Limited_quote&) entry -> ";
    if(this != &rhs){
        Disc_quote::operator=(rhs);
    }
    cout << "operator=(const Limited_quote&) exit" << endl;
    return *this;
}
inline Limited_quote& Limited_quote::operator=(const Limited_quote&& rhs)
{
    cout << "operator=(Limited_quote&&) entry -> ";
    if(this != &rhs){
        Disc_quote::operator=(std::move(rhs));
    }
    cout << "operator=(Limited_quote&&) exit" << endl;
    return *this;
}
