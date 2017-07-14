// strblobptr.h -- StrBlobPtr companion pointer class for the StrBlob class
#ifndef STRBLOBPTR_H_
#define STRBLOBPTR_H_

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include "strblob.h"


// StrBlobPtr throws an exception on attempts to access a nonexistent element
class StrBlobPtr
{
public:
    StrBlobPtr()
        : curr(0) { }
    StrBlobPtr(StrBlob& a, size_t sz=0)
        : wptr(a.data), curr(sz) { }

    bool operator==(const StrBlobPtr& rhs) const
        { return curr == rhs.curr; }
    bool operator!=(const StrBlobPtr& rhs) const
        { return !(*this == rhs); }

    std::string& deref() const;
    std::string& operator*() const
    {
        std::shared_ptr<std::vector<std::string>> p =
            check(curr, "dereference past end");
        return (*p)[curr];  // (*p) is the vector to which this object points
    }
    // operator->() must return a pointer to a class type, or an object of a class
    // that defines its own operator arrow
    std::string* operator->() const
    {
        // delegate the real work to the dereference operator
        return &(this->operator*());
    }
    
    StrBlobPtr& incr(); // prefix version
    StrBlobPtr& operator++();       // prefix operators
    StrBlobPtr& operator--();
    StrBlobPtr operator++(int);     // postfix operators
    StrBlobPtr operator--(int);
    StrBlobPtr& operator+=(std::size_t n);
    StrBlobPtr operator+(std::size_t n);
    StrBlobPtr& operator-=(std::size_t n);
    StrBlobPtr operator-(std::size_t n);

    
    std::string& operator[](int n) const;

private:
// check returns a shared_ptr to the vector if check succeeds
    std::shared_ptr<std::vector<std::string>>
        check(std::size_t, const std::string&) const;

    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;       // current position within the array
};


inline std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check(std::size_t i, const std::string& msg) const
{
    std::shared_ptr<std::vector<std::string>> ret = wptr.lock();
    if( !ret )
        throw std::runtime_error("unbount StrBlobPtr");
    if( i >= ret->size() )
        throw std::out_of_range(msg);
    
    return ret;
}


inline std::string& StrBlobPtr::deref() const
{
    std::shared_ptr<std::vector<std::string>> p = check(curr, "dereference past end");
    return (*p)[curr];
}

// prefix: return a reference to the incremented object
inline StrBlobPtr& StrBlobPtr::incr()
{
    // if curr already points past the end of the container can't increment it
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

inline StrBlobPtr StrBlob::begin()
    { return StrBlobPtr(*this); }
inline StrBlobPtr StrBlob::end()
    { return StrBlobPtr(*this, data->size()); }

inline std::string& StrBlobPtr::operator[](int n) const
{
    std::shared_ptr<std::vector<std::string>> p = check(curr + n, "bad index");
    if( n < 0 )
        throw std::out_of_range("bad idnex");
    return (*p)[curr+n];
}

inline StrBlobPtr& StrBlobPtr::operator++()
{
    // if curr already points past the end of the container, can't increment it
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

inline StrBlobPtr& StrBlobPtr::operator--()
{
    // if curr is zero, decrementing it will yield an invalid subscript
    --curr;
    check(-1, "decrement past begin of StrBlobPtr");
    return *this;
}

inline StrBlobPtr StrBlobPtr::operator++(int)
{
    // no check needed here; the call to prefix increment will do the check
    StrBlobPtr ret = *this; // save the current value
    ++*this;        // advance one element: prefix ++ check the increment
    return ret;
}

inline StrBlobPtr StrBlobPtr::operator--(int)
{
    // no check needed here, the call to prefix decrement will do the check
    StrBlobPtr ret = *this; // save the current value
    --*this;        // move backward one element; prefix -- check the decrement
    return ret;
}

inline StrBlobPtr& StrBlobPtr::operator+=(std::size_t n)
{
    check(curr+n, "int increment past end");
    curr += n;
    return *this;
}

inline StrBlobPtr StrBlobPtr::operator+(std::size_t n)
{
    StrBlobPtr ret(*this);
    ret += n;
    return ret;
}

inline StrBlobPtr& StrBlobPtr::operator-=(std::size_t n)
{
    curr -= n;
    check(-1, "int decrement past begin of StrBlobPtr");
    return *this;
}

inline StrBlobPtr StrBlobPtr::operator-(std::size_t n)
{
    StrBlobPtr ret(*this);
    ret -= n;
    return *this;
}


#endif /*STRBLOBPTR_H_*/
