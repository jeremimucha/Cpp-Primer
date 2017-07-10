// ex 13.13
/*A good way to understand copy-control members and
constructors is to define a simple class with these members in which each
member prints its name:
Code:
struct X {
X() {std::cout << "X()" << std::endl;}
X(const X&) {std::cout << "X(const X&)" << std::endl;}
};
Add the copy-assignment operator and destructor to  X and write a program
using  X objects in various ways: Pass them as nonreference and reference
parameters; dynamically allocate them; put them in containers; and so forth.
Study the output until you are certain you understand when and why each
copy-control member is used. As you read the output, remember that the
compiler can omit calls to the copy constructor.*/
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;


struct X
{
    X()
        {cout << "X()" <<endl;}
    X(const X&)
        {cout << "X(const X&)" << endl;}
    X& operator=(const X&)
        {cout << "operator=(const X&)" << endl; return *this;}
    ~X()
        {cout << "~X()" << endl;}
};

X makeX() { return X(); }
X& useX(X& x) { return x; }
X copyX(X x) { return x; }
X derefX(X* px) { return *px; }

int main()
{
    X x1;
    X x2(x1);
    X x3;
    x3 = X();
    vector<X> vx;
    X* px2 = new X;

    *px2 = makeX();
    *px2 = useX(x1);
    x2 = copyX(x1);
    x3 = derefX(px2);

    // vx.push_back(makeX());

    delete px2;
}
