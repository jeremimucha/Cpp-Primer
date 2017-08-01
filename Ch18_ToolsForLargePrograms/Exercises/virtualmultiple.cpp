/* Exercise 18.29: Given the following class hierarchy:
Code:
class Class { ... };
class Base : public Class { ... };
class D1 : virtual public Base { ... };
class D2 : virtual public Base { ... };
class MI : public D1, public D2 { ... };
class Final : public MI, public Class { ... };
(a) In what order are constructors and destructors run on a  Final object?
(b) A  Final object has how many  Base parts? How many  Class parts?
(c) Which of the following assignments is a compile-time error?
Base *pb; Class *pc; MI *pmi; D2 *pd2;
(a)  pb = new Class;
(b)  pc = new Final;
(c)  pmi = pb;
(d)  pd2 = pmi;
 */
#include <iostream>
using std::cout;
using std::endl;


class Class
{
public:
    Class() noexcept { cout <<"Class()" << endl; }
    virtual ~Class() noexcept { cout << "~Class()" << endl; }
    int ci;
};

class Base : public Class
{
public:
    Base() noexcept { cout << "Base()" << endl; }
    Base(int i) noexcept
        : Class(), bi(i)
        { cout << "Base(int)" << endl; }
    Base(const Base& b) noexcept
        : Class(b), bi(b.bi)
        { cout << "Base(const Base&)" << endl; }
    virtual ~Base() noexcept { cout << "~Base()" << endl; }
    int bi;
};

class D1 : virtual public Base
{
public:
    D1() noexcept { cout << "D1()" << endl; }
    D1(int i) noexcept
        : Base(i)
        { cout << "D1(int)" << endl; }
    D1(const D1& other) noexcept
        : Base(other)
        { cout << "D1(const D1&)" << endl; }
    virtual ~D1() noexcept { cout << "~D1()" << endl; }
};

class D2 : virtual public Base
{
public:
    D2() noexcept { cout << "D2()" << endl; }
    D2(int i) noexcept
        : Base(i)
        { cout << "D2(int)" << endl; }
    D2(const D2& other) noexcept
        : Base(other)
        { cout << "D2(const D2&)" << endl; }
    virtual ~D2() noexcept { cout << "~D2()" << endl; }
};

class MI : public D1, public D2
{
public:
    MI() noexcept { cout << "MI()" << endl; }
    MI(int i) noexcept
        : Base(i), D1(i), D2(i)
        { cout << "MI(int)" << endl; }
    MI(const MI& other) noexcept
        : Base(other), D1(other), D2(other)
        { cout << "MI(const MI&)" << endl; }
    virtual ~MI() noexcept { cout << "~MI()" << endl; }
};

class Final : public MI, public Class   // Class is an inacessible ambiguous base class
{
public:
    Final() noexcept { cout << "Final()" << endl; }
    Final(int i) noexcept
        : Base(i), MI(i), Class()
        { cout << "Final(int)" << endl; }
    Final(const Final& other) noexcept
        : Base(other), MI(other), Class{}
        { cout << "Final(const Final&)" << endl; }
    virtual ~Final() noexcept { cout << "~Final()" << endl; }
};


int main()
{
    Final f(42);
}
