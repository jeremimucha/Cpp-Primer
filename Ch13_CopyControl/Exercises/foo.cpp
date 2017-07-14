// exs 13.6.3
/*
Exercise 13.56: What would happen if we defined  sorted as:
Code:
    Foo Foo::sorted() const & {
        Foo ret(*this);
        return ret.sorted();
    }
Exercise 13.57: What if we defined  sorted as:
Code:
    Foo Foo::sorted() const & { return Foo(*this).sorted(); }
Exercise 13.58: Write versions of class  Foo with print statements in their
sorted functions to test your answers to the previous two exercises.
*/
#include <iostream>
#include <utility>
#include <vector>
#include <initializer_list>
#include <algorithm>
using std::cout;
using std::endl;
using std::vector;


class Foo
{
public:
    Foo() { cout << "Foo()\n"; }
    Foo(std::initializer_list<int> il)
        : data(il.begin(), il.end())
        { cout << "Foo(initializer_list<int>)\n"; }
    Foo(const Foo& f)
        : data(f.data)
        { cout << "Foo(const Foo&)\n"; }
    Foo(Foo&& f)
        : data(std::move(f.data))
        { cout << "Foo(Foo&&)\n"; }
    Foo operator=(const Foo& rhs)
    {
        cout << "Foo::operator=(const Foo&)\n";
        data = rhs.data;
        return *this;
    }
    Foo operator=(Foo&& rhs)
    {
        cout << "Foo::operator=(Foo&&)\n";
        data = std::move(rhs.data);
        return *this;
    }
    Foo sorted() &&;            // may run on modifiable rvalues
    Foo sorted() const &;       // may run on any kind of Foo

friend std::ostream& operator<<(std::ostream& os, const Foo& f);
private:
    vector<int> data;
};

inline Foo Foo::sorted() &&
{
    cout << "Foo::sorted() &&\n";
    std::sort(data.begin(), data.end());
    return *this;
}

// inline Foo Foo::sorted() const &
// {
//     cout << "Foo:sorted() const&\n";
//     Foo ret(*this);
//     std::sort(ret.data.begin(), ret.data.end());
//     return ret;
// }

/* This definition would result in a recursive call */
/* ------------------------------------------------------------------------- */
// inline Foo Foo::sorted() const &
// {
//     cout << "Foo::sorted() const&\n";
//     Foo ret(*this);
//     return ret.sorted();
// }
/* ------------------------------------------------------------------------- */

/*  */
/* ------------------------------------------------------------------------- */
inline Foo Foo::sorted() const &
{
    cout << "Foo::sorted() const&\n";
    return Foo(*this).sorted();
}
/* ------------------------------------------------------------------------- */


std::ostream& operator<<(std::ostream& os, const Foo& f)
{
    for(int i : f.data)
        os << i << ", ";
    return os;
}

int main()
{
    Foo f1{42,11,9,17,13,11,0};
    Foo f2 = f1.sorted();
    Foo f3 = Foo({11,42,8,7,4,0,345}).sorted();
    cout << "f1: " << f1 << endl;
    cout << "f2: " << f2 << endl;
    cout << "f3: " << f3 << endl;
}
