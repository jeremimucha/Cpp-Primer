// xy.cpp -- Chapter 7 - ex7.31
// Define a pair of classes X and Y, in which X has a pointer to Y
// and Y has an object of type X.
// Using smart pointers
#include <iostream>
#include <memory>
#include <utility>


class Y;

class X
{
private:
    std::unique_ptr<Y> py;
public:
    X() : py(nullptr) { }
    X(const Y& y) : py(new Y(y)) { }
    X(const X& x) : py(new Y(*x.py) { }     // copy ctor
    X(X&& x) : py(std::move(x.py)) { }      // move ctor
    const X& operator=(const X& x)
        { if(this == &x) return *this; *py = *x.py; return *this; }
    const X& operator(X&& x)
        { if(this == &x) return *this; py = nullptr; py.swap(x.py); return *this; }
    // destructor isn't needed because - unique_ptr will handle destruction
    // ~X() { delete py; }
};


class Y
{
private:
    X x;
public:
    Y() = default;
    Y(const X& xval) : x(xval) { }
    // default copy ctor, copy assignment, move ctor and move assignment are OK
};
