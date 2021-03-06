// ex 13.8
/*Write the assignment operator for the  HasPtr class from
exercise 13.5 in § 13.1.1 (p. 499). As with the copy constructor, your
assignment operator should copy the object to which  ps points.*/
#include <iostream>
#include <string>
using std::cout;
using std::string;


class HasPtr
{
public:
    HasPtr(const std::string& s=std::string())
        : ps(new std::string(s)), i(0)
        { }
    HasPtr(const HasPtr& rhs)
        : ps(new std::string(*rhs.ps)), i(rhs.i)
        { }
    HasPtr& operator=(const HasPtr& p);
friend std::ostream& operator<<(std::ostream& os, const HasPtr& hp);
private:
    std::string* ps;
    int i;
};


int main()
{
    HasPtr hp("original HasPtr");
    HasPtr chp(hp);

    cout << "hp: " << hp << "\n";
    cout << "chp: " << chp << "\n";

    HasPtr hp2("another HasPtr");
    cout << "hp2 before assignment: " << hp2 << "\n";
    hp2 = hp;
    cout << "hp2 after assignment: " << hp2 << "\n";
}


HasPtr& HasPtr::operator=(const HasPtr& p)
{
    if( this == &p )
        return *this;
    *ps = *p.ps;
    i = p.i;
    return *this;
}


std::ostream& operator<<(std::ostream& os, const HasPtr& hp)
{
    return os << *hp.ps << ", 0x" << reinterpret_cast<void*>(hp.ps)
              << ", i = " << hp.i;
}
