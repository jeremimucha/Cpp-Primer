/* Exercise 19.3: Given the following class hierarchy in which each class
defines a  public default constructor and virtual destructor:
Code:
class A {  };
class B : public A {  };
class C : public B {  };
class D : public B, public A {  };
which, if any, of the following  dynamic_cast s fail?
(a) A *pa = new C;
B *pb = dynamic_cast< B* >(pa);
(b) B *pb = new B;
C *pc = dynamic_cast< C* >(pb);
(c) A *pa = new D;
B *pb = dynamic_cast< B* >(pa);
*/
#include <iostream>
using std::cout;
using std::endl;
using std::cerr;


class A { 
public:
    A() = default;
    virtual ~A() = default;
 };
class B : public A { 
public:
    B() = default;
    virtual ~B() = default;
 };
class C : public B { 
public:
    C() = default;
    virtual ~C() = default;
 };
class D : public B, public A { // A inaccessible due to ambiguity
public:
    D() = default;
    virtual ~D() = default;
 };


 int main()
 {
    A* pa = new C;
    B* pb = dynamic_cast<B*>(pa);
    if( pb )
        cerr << "dynamic_cast<B*>(pa) succeeds" << endl;    // this is true 
    else
        cerr << "dynamic_cast<B*>(pa) returns a nullptr" << endl;
    pb = new B;
    C *pc = dynamic_cast< C* >(pb);
    if( pc )
        cerr << "dynamic_cast<C*>(pb) succeeds" << endl;
    else
        cerr << "dynamic_cast<C*>(pb) returns a nullptr" << endl;  // this is true

    delete pa;
    delete pb;

    // pa = new D;     // illegal - A is an ambiguous base of D - can't point to it
    // pb = dynamic_cast<B*>(pa);
    // if( pb )
    //     cerr << "dynamic_cast<B*>(pa) succeeds" << endl;
    // else
    //     cerr << "dynamic_cast<B*>(pa) returns a nullptr" << endl;
 }
