// ConstStrBlobPtr - pointer class to a const StrBlob
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

    const std::string& deref() const;   // dereference as const
    ConstStrBlobPtr& incr(); // prefix version
    bool operator==(const ConstStrBlobPtr& rhs)
        { return curr == rhs.curr; }
    bool operator!=(const ConstStrBlobPtr& rhs)
        { return curr != rhs.curr; }
private:
// check returns a shared_ptr to the vector if check succeeds
    std::shared_ptr<std::vector<std::string>>
        check(std::size_t, const std::string&) const;

    std::weak_ptr<std::vector<std::string>> wptr;     // constant reference;
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
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

inline ConstStrBlobPtr StrBlob::cbegin() const
    { return ConstStrBlobPtr(*this); }
inline ConstStrBlobPtr StrBlob::cend() const
    { return ConstStrBlobPtr(*this, data->size()); }


#endif /*CONSTSTRBLOBPTR_H_*/
