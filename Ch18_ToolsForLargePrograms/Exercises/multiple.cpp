/* Exercise 18.26: Given the hierarchy in the box on page 810, why is the
following call to  print an error? Revise  MI to allow this call to  print to
compile and execute correctly.
MI mi;
mi.print(42);
Exercise 18.27: Given the class hierarchy in the box on page 810 and
assuming we add a function named  foo to MI as follows:
int ival;
double dval;
void MI::foo(double cval)
{
int dval;
// exercise questions occur here
}
(a) List all the names visible from within  MI::foo .
(b) Are any names visible from more than one base class?
(c) Assign to the local instance of  dval the sum of the  dval member of
Base1 and the  dval member of  Derived .
(d) Assign the value of the last element in  MI::dvec to  Base2::fval .
(e) Assign  cval from  Base1 to the first character in  sval from  Derived . */
#include <iostream>
#include <string>
#include <vector>


struct Base1
{
    void print(int i) const
        { std::cout << "Base1::print(" << i << ")" << std::endl; }
protected:
    int     ival{1};
    double  dval{1.1};
    char    cval{'1'};
private:
    int     *id{&ival};
};


struct Base2
{
    void print(double d) const
        { std::cout << "Base2::print(" << d << ")" << std::endl; }
protected:
    double  fval{2.2};
// private:
    double  dval{2.222};
};


struct Derived : public Base1
{
    void print(std::string& s) const
        { std::cout << "Derived::print(" << s << ")" << std::endl; }
protected:
    std::string sval{"Derived"};
    double      dval{3.3};
};


struct MI : public Derived, public Base2
{
    void print(std::vector<double>);
    void print(int i) const
        { Base1::print(i); }
    void foo(double cval)
    {
        int dval = 4.4;
        std::cerr << "cval: " << cval << "\n"
                  << "dval: " << dval << "\n"
                  << "Derived::dval: " << Derived::dval << "\n"
                  << "Base2::dval: " << Base2::dval << "\n"
                  << "Base1::dval: " << Base1::dval << "\n";
    }
protected:
    int                 *ival;
    std::vector<double> dvec;
};

int ival;
double dval;

int main()
{
    MI mi;
    mi.print(42);
    mi.foo(11);
}
