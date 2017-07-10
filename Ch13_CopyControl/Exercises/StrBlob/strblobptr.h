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

    std::string& deref() const;
    StrBlobPtr& incr(); // prefix version
    bool operator==(const StrBlobPtr& rhs) const
        { return curr == rhs.curr; }
    bool operator!=(const StrBlobPtr& rhs) const
        { return !(*this == rhs); }
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

#endif /*STRBLOBPTR_H_*/
