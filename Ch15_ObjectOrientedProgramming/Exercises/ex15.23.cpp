/* Exercise 15.23: Assuming class  D1 on page 620 had intended to override
its inherited  fcn function, how would you fix that class? Assuming you fixed
the class so that  fcn matched the definition in  Base , how would the calls in
that section be resolved? */
#include <iostream>
using std::cout;
using std::endl;


class Base
{
public:
    virtual int fcn() { cout << "Base::fcn()" << endl; return 0; }
};

class D1 : public Base
{
public:
// overrides virtual function in base,
// can be called through Base*, Base&, D1* or D1&
    int fcn() { cout << "D1::fcn()" << endl; return 1; }
// non-virtual member function, can be called through D1* or D1&
// but not through Base* or Base&
    int fcn(int i) { cout << "D1::fcn(int)" << endl; return i; }
// new virtual function that does not exist in Base
// can be called through D1* and D1&
    virtual void f2() { cout << "D1::f2()" << endl; }
};

class D2 : public D1
{
public:
// overrides virtual fcn in Base,
// can be called through Base*, Base&, D1*, D1&, D2* and D2&
    int fcn() { cout << "D2::fcn()" << endl; return 2; }
// non-virtual function; hides D1::fcn(int);
    int fcn(int i) { cout << "D2::fcn(int)" << endl; return i*2; }
// Overrides virtual f2 in D1, ca nbe called through D1*, D1&, D2* or D2&
    void f2() { cout << "D2::f2()" << endl; }
};


int main()
{
    Base bobj;
    D1 d1obj;
    D2 d2obj;
    Base *bp1 = &bobj
        ,*bp2 = &d1obj
        ,*bp3 = &d2obj
        ;

    bp1->fcn();     // virtual call, will call Base::fcn() at run time
    bp2->fcn();     // vritual call, will call D1::fcn() at run time
    bp3->fcn();     // virtual call, will call D2::fcn() at run time

    D1 *d1p = &d1obj;
    D2 *d2p = &d2obj;
    // bp2->f2();      // error: Base has no member named f2
    d1p->f2();      // virtual call, will call D1:f2() at run time
    d2p->f2();      // virtual call, will call D2:f2() at run time

    Base *p1 = &d2obj;
    D1 *p2 = &d2obj;
    D2 *p3 = &d2obj;
    // p1->fcn(42);    // error: Base has no version of fcn that takes an int
    p2->fcn(42);    // statically bound, calls D1::fcn(int)
    p3->fcn(42);    // statically bound, calls D2::fcn(int)

    D1 *d1pd2 = &d2obj;
    d1pd2->fcn(42); // statically bound, calls D2::fcn(int)
    d1pd2->fcn();   // virtual call, calls D2::fcn() at run time
    d1pd2->f2();    // virtual call, calls D2::f2() at run time
}
