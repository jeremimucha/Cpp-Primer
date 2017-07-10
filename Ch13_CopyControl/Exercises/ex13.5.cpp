// ex 13.5
/*Given the following sketch of a class, write a copy
constructor that copies all the members. Your constructor should
dynamically allocate a new  string (§ 12.1.2, p. 458) and copy the object
to which  ps points, rather than copying  ps itself.*/
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
}


std::ostream& operator<<(std::ostream& os, const HasPtr& hp)
{
    return os << *hp.ps << ", 0x" << reinterpret_cast<void*>(hp.ps)
              << ", i = " << hp.i;
}
