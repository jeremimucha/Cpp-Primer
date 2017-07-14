// conststrblobptr.h -- 
#ifndef CONSTSTRBLOBPTR_H_
#define CONSTSTRBLOBPTR_H_

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include "strblob.h"


class ConstStrBlobPtr
{
public:
    ConstStrBlobPtr()
        : curr(0) { }
    ConstStrBlobPtr(const StrBlob& a, size_t sz=0)
        : wptr(a.data), curr(sz) { }

    bool operator==(const ConstStrBlobPtr& rhs) const
        { return curr == rhs.curr; }
    bool operator!=(const ConstStrBlobPtr& rhs) const
        { return !(*this == rhs); }

    const std::string& deref() const;
    const std::string& operator*() const
    {
        std::shared_ptr<std::vector<std::string>> p =
            check(curr, "dereference past end");
        return (*p)[curr];
    }
    const std::string* operator->() const
    {
        return &(this->operator*());
    }
    
    ConstStrBlobPtr& incr(); // prefix version
    const std::string& operator[](int n) const;
    ConstStrBlobPtr& operator++();       // prefix operators
    ConstStrBlobPtr& operator--();
    ConstStrBlobPtr operator++(int);     // postfix operators
    ConstStrBlobPtr operator--(int);
    ConstStrBlobPtr& operator+=(std::size_t n);
    ConstStrBlobPtr operator+(std::size_t n);
    ConstStrBlobPtr& operator-=(std::size_t n);
    ConstStrBlobPtr operator-(std::size_t n);
private:
// check returns a shared_ptr to the vector if check succeeds
    std::shared_ptr<std::vector<std::string>>
        check(std::size_t, const std::string&) const;

    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;       // current position within the array
};


inline std::shared_ptr<std::vector<std::string>>
ConstStrBlobPtr::check(std::size_t i, const std::string& msg) const
{
    std::shared_ptr<std::vector<std::string>> ret = wptr.lock();
    if( !ret )
        throw std::runtime_error("unbount ConstStrBlobPtr");
    if( i >= ret->size() )
        throw std::out_of_range(msg);
    
    return ret;
}


inline const std::string& ConstStrBlobPtr::deref() const
{
    std::shared_ptr<std::vector<std::string>> p = check(curr, "dereference past end");
    return (*p)[curr];
}

// prefix: return a reference to the incremented object
inline ConstStrBlobPtr& ConstStrBlobPtr::incr()
{
    // if curr already points past the end of the container can't increment it
    check(curr, "increment past end of ConstStrBlobPtr");
    ++curr;
    return *this;
}

inline ConstStrBlobPtr StrBlob::cbegin() const
    { return ConstStrBlobPtr(*this); }
inline ConstStrBlobPtr StrBlob::cend() const
    { return ConstStrBlobPtr(*this, data->size()); }

inline const std::string& ConstStrBlobPtr::operator[](int n) const
{
    std::shared_ptr<std::vector<std::string>> p = check(curr, "bad index");
    if( n < 0 )
        throw std::out_of_range("bad index");
    return (*p)[curr+n];
}

inline ConstStrBlobPtr& ConstStrBlobPtr::operator++()
{
    // if curr already points past the end of the container, can't increment it
    check(curr, "increment past end of ConstStrBlobPtr");
    ++curr;
    return *this;
}

inline ConstStrBlobPtr& ConstStrBlobPtr::operator--()
{
    // if curr is zero, decrementing it will yield an invalid subscript
    --curr;
    check(-1, "decrement past begin of ConstStrBlobPtr");
    return *this;
}

inline ConstStrBlobPtr ConstStrBlobPtr::operator++(int)
{
    // no check needed here; the call to prefix increment will do the check
    ConstStrBlobPtr ret = *this; // save the current value
    ++*this;        // advance one element: prefix ++ check the increment
    return ret;
}

inline ConstStrBlobPtr ConstStrBlobPtr::operator--(int)
{
    // no check needed here, the call to prefix decrement will do the check
    ConstStrBlobPtr ret = *this; // save the current value
    --*this;        // move backward one element; prefix -- check the decrement
    return ret;
}

inline ConstStrBlobPtr& ConstStrBlobPtr::operator+=(std::size_t n)
{
    check(curr+n, "int increment past end");
    curr += n;
    return *this;
}

inline ConstStrBlobPtr ConstStrBlobPtr::operator+(std::size_t n)
{
    ConstStrBlobPtr ret(*this);
    ret += n;
    return ret;
}

inline ConstStrBlobPtr& ConstStrBlobPtr::operator-=(std::size_t n)
{
    curr -= n;
    check(-1, "int decrement past begin of ConstStrBlobPtr");
    return *this;
}

inline ConstStrBlobPtr ConstStrBlobPtr::operator-(std::size_t n)
{
    ConstStrBlobPtr ret(*this);
    ret -= n;
    return *this;
}

#endif /*CONSTSTRBLOBPTR_H_*/
