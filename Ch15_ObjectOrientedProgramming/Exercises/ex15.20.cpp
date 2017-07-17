/* Exercise 15.18: Given the classes from page 612 and page 613, and
assuming each object has the type specified in the comments, determine
which of these assignments are legal. Explain why those that are illegal
aren’t allowed:
Code:
Base *p = &d1; // d1 has type Pub_Derv
p = &d2; // d2 has type Priv_Derv
p = &d3; // d3 has type Prot_Derv
p = &dd1; // dd1 has type Derived_from_Public
p = &dd2; // dd2 has type Derived_from_Private
p = &dd3; // dd3 has type Derived_from_Protected
Exercise 15.19: Assume that each of the classes from page 612 and page
613 has a member function of the form:
void memfcn(Base &b) { b = *this; }
For each class, determine whether this function would be legal.
Exercise 15.20: Write code to test your answers to the previous two
exercises. */
#include <iostream>
using std::cout;
using std::endl;



class Base
{
public:
    void pub_mem();
protected:
    int prot_mem;
private:
    char priv_mem;
};


struct Pub_Derv : public Base
{
    // ok: derived classes can access protected members
    int f() { return prot_mem; }
    // error: private members are inaccessible to derived classes
    // char g() { return priv_mem; }

// OK: Base subobject is public and accessible in this scope
    void memfcn(Base& b) { b = *this; }
};

struct Prot_Derv : protected Base
{
    // ok: protected derivation doesn't affect acces in the derived class
    int f2() const { return prot_mem; }

// OK: Base subobject is protected but accessible in this scope
    void memfcn(Base& b) { b = *this; }
};

struct Priv_Derv : private Base
{
    // private derivation doesn't affect access in the derived class
    int f1() const { return prot_mem; }

// OK: Base subobject is private but accessible in this scope
    void memfcn(Base& b) { b = *this; }
};

struct Derived_from_Public : public Pub_Derv
{
    // ok: base::prot_mem remains protected in Pub_Derv
    int use_base() { return prot_mem; }

// OK: Base subobject is public and accessible in this scope
    void memfcn(Base& b) { b = *this; }
};

struct Derived_from_Protected : public Prot_Derv
{
    // ok: base::prot remains protected in Prot_Derv
    int use_base() { return prot_mem; }

// OK: Base subobject is protected by the Prot_Derv class and accessible in this scope
    void memfcn(Base& b) { b = *this; }
};

struct Derived_from_Private : public Priv_Derv
{
    // error: Base::prot_mem is private in Priv_Deriv
    // int use_base() { return prot_mem; }

// error: Base subobject is private to the Priv_Derv class and innaccessbile in this scope
    // void memfcn(Base& b) { b = *this; }
};


int main()
{
    Pub_Derv d1;
    Priv_Derv d2;
    Prot_Derv d3;
    Derived_from_Public dd1;
    Derived_from_Private dd2;
    Derived_from_Protected dd3;

    
    Base* p = nullptr;
    
// OK: the Base subobject is publicly accessible from obj of type Pub_Derv
    p = &d1; // d1 has type Pub_Derv

// error: the Base subobject is private to the obj of Priv_Derv type
    // p = &d2; // d2 has type Priv_Derv

// error: the Base subobject is protected by the obj of Prot_Derv type
    // p = &d3; // d3 has type Prot_Derv

// OK: the Base subobject is publicy accessible
    p = &dd1; // dd1 has type Derived_from_Public

// error: the Base subobject is private
    // p = &dd2; // dd2 has type Derived_from_Private

// error: the Base subobject is protected
    // p = &dd3; // dd3 has type Derived_from_Protected
}
