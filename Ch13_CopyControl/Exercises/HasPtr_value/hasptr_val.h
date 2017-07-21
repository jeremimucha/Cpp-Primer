#ifndef HASPTR_H_
#define HASPTR_H_

#include <iostream>
#include <utility>
#include <memory>


class HasPtr
{
public:
    HasPtr(const std::string& s=std::string())
        : ps(new std::string(s)), i(0)
        { info("HasPtr(const string&)", ps, i); }

    HasPtr(const HasPtr& rhs)
        : ps(new std::string(*rhs.ps)), i(rhs.i)
        { info("HasPtr(const HasPtr&)", ps, i); }

    HasPtr(HasPtr&& rhs) noexcept
    // rhs is an lvalue, like any other variable - we need to std::move it to
    // convert it to a movable rvalue
        : ps(std::move(rhs.ps)), i(rhs.i)
        {
            info("HasPtr(HasPtr&&)", ps, i);
            rhs.ps = nullptr;
            rhs.i = 0;
        }

    ~HasPtr()
        { info("--> ~HasPtr()", ps, i); delete ps; }

    HasPtr& operator=(const HasPtr& p);
    HasPtr& operator=(HasPtr&& p) noexcept;

    // copy-and-swap type of assignment operator
    // HasPtr& operator=(HasPtr rhs)
    //     {
    //         // swap the contents of the left-hand operand with the local variable rhs
    //         swap(*this, rhs);
    //         return *this;
    //     }

    friend bool operator<(const HasPtr& lhs, const HasPtr& rhs);
    friend void swap(HasPtr&, HasPtr&) noexcept;
    friend std::ostream& operator<<(std::ostream& os, const HasPtr& hp);


private:
    std::string* ps;
    int i;

    static void info(const char* str, const std::string* ps, int i)
    {
        std::cout << str << ", ps: " << reinterpret_cast<const void*>(ps)
                    << ", *ps: " << *ps << ", i: " << i << "\n";
    }
};

inline void swap(HasPtr& lhs, HasPtr& rhs) noexcept
{
    using std::swap;
    // std::cout << "swap(HasPtr& lhs, HasPtr& rhs):";
    // std::cout << "\n\tlhs.ps: " << reinterpret_cast<void*>(lhs.ps)
    //         << ", *lhs.ps: " << *lhs.ps << ", lhs.i: " << lhs.i;
    // std::cout << "\n\trhs.ps: " << reinterpret_cast<void*>(rhs.ps)
    //         << ", *rhs.ps: " << *rhs.ps << ", rhs.i: " << rhs.i
    //         << "\n";
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
    // std::string* newp = new std::string(*p.ps);
    // delete ps;
    // ps = newp;
    // i = p.i;
    // return *this;
}

inline HasPtr& HasPtr::operator=(HasPtr&& p) noexcept
{
    if( this == &p )
        return *this;
    delete ps;
    // ps = p.ps;
    ps = std::move(p.ps);
    i = p.i;
    p.ps = nullptr;
    p.i = 0;
    info("HasPtr::operator=(const HasPtr&)", ps, i);
    return *this;
}

inline bool operator<(const HasPtr& lhs, const HasPtr& rhs)
{
    return *lhs.ps < *rhs.ps;
}

inline std::ostream& operator<<(std::ostream& os, const HasPtr& hp)
{
    return os << *hp.ps << ", 0x" << reinterpret_cast<void*>(hp.ps)
              << ", i = " << hp.i;
}


#endif /*HASPTR_H_*/
