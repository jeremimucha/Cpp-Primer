#ifndef HASPTR_H_
#define HASPTR_H_

#include <iostream>


class HasPtr
{
public:
friend void swap(HasPtr&, HasPtr&) noexcept;
    HasPtr(const std::string& s=std::string())
        : ps(new std::string(s)), i(0)
        { info("HasPtr(const string&)", ps, i); }
    HasPtr(const HasPtr& rhs)
        : ps(new std::string(*rhs.ps)), i(rhs.i)
        { info("HasPtr(const HasPtr&)", ps, i); }
    ~HasPtr() { info("--> ~HasPtr()", ps, i); delete ps; }
    HasPtr& operator=(const HasPtr& p);
    // bool operator<(HasPtr& rhs)
    //     { return &ps < *rhs.ps; }
    bool operator<(const HasPtr& rhs) const
        { return *ps < *rhs.ps; }
    void swap(HasPtr& rhs)
        {
            using std::swap;
            swap(ps, rhs.ps);
            swap(i, rhs.i);
        }

friend std::ostream& operator<<(std::ostream& os, const HasPtr& hp);
private:
    std::string* ps;
    int i;

    static void info(const char* str, std::string* ps, int i)
    {
        std::cout << str << ", ps: " << reinterpret_cast<void*>(ps)
                    << ", *ps: " << *ps << ", i: " << i << "\n";
    }
};


inline void swap(HasPtr& lhs, HasPtr& rhs) noexcept
{
    using std::swap;
    std::cout << "HasPtr::swap(HasPtr& lhs, HasPtr& rhs):";
    std::cout << "\n\tlhs.ps: " << reinterpret_cast<void*>(lhs.ps)
              << ", *lhs.ps: " << *lhs.ps << ", lhs.i: " << lhs.i;
    std::cout << "\n\trhs.ps: " << reinterpret_cast<void*>(rhs.ps)
              << ", *rhs.ps: " << *rhs.ps << ", rhs.i: " << rhs.i
              << "\n";
    swap(lhs.ps, rhs.ps);   // swap the pointers, rather than string data
    swap(lhs.i, rhs.i);     // swap ints
}

inline HasPtr& HasPtr::operator=(const HasPtr& p)
{
    info("HasPtr::operator=(const HasPtr&)", ps, i);
    if( this == &p )
        return *this;
    *ps = *p.ps;
    i = p.i;
    return *this;
}

inline std::ostream& operator<<(std::ostream& os, const HasPtr& hp)
{
    return os << *hp.ps << ", 0x" << reinterpret_cast<void*>(hp.ps)
              << ", i = " << hp.i;
}


#endif /*HASPTR_H_*/
