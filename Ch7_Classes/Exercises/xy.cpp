// xy.cpp -- Chapter 7 - ex7.31
// Define a pair of classes X and Y, in which X has a pointer to Y
// and Y has an object of type X
#include <iostream>


class Y;

class X
{
private:
    Y* py;
public:
    X() : py(nullptr) { }
    X(const Y& y) : py(new Y(y)) { }
    X(const X& x) : py(new Y(*x.py)) { }
    X(X&& x) : py(x.py) { x.py = nullptr; }
    X& operator=(const X& x)
        { if(this == &x) return *this; delete py; py = new Y(*x.py); return *this; }
    X& operator(X&& x)
        { if(this == &x) return *this; delete py; py=x.py; x.py=nullptr; return *this; }
    ~X() { delete py; }
};


class Y
{
private:
    X x;
public:
    Y() = default;
    Y(const X& xval) : x(xval) { }
};
