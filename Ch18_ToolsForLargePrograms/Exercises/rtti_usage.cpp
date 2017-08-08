/* Usage of the typeid operator to implement an equality operator
   for a class hierarchy.
*/
#include <iostream>
#include <typeinfo>


class Base
{
    friend bool operator==(const Base&, const Base&);
public:
    Base() = default;
    Base(int ii)
        : b(ii) { }
protected:
    virtual bool equal(const Base&) const;

    int b;
};

class Derived : public Base
{
public:
    Derived() = default;
    Derived(int dd)
        : Base(dd/2), d(dd) { }
protected:
    bool equal(const Base&) const;

    int d;
};


bool operator==(const Base& lhs, const Base& rhs)
{
    // returns false if typeids are different otherwise
    // makes a virtual call to equal
    return typeid(lhs) == typeid(rhs) && lhs.equal(rhs);
}

bool Base::equal(const Base& rhs) const
{
    // do the work required to compare to Base objects
    return b == rhs.b;
}

bool Derived::equal(const Base& rhs) const
{
    // we know the types are equal, so the cast won't throw
    const Derived& r = dynamic_cast<const Derived&>(rhs);
    // do the work to compare two Derived objects and return the result
    return Base::equal(r) && d == r.d;
}

int main()
{
    Base b1(42);
    Base b2(42);
    Derived d1(11);
    Derived d2(11);
    std::cout << std::boolalpha;
    std::cout << "b1 == b2 " << (b1 == b2) << std::endl;
    std::cout << "d1 == d2 " << (d1 == d2);
}
