#ifndef STRBLOBPTRPTR_H_
#define STRBLOBPTRPTR_H_

#include <iostream>
#include <memory>
#include <utility>

// class that holds a pointer to StrBlobPtr
class StrBlobPtrPtr
{
public:
    StrBlobPtrPtr() = default;
    StrBlobPtrPtr(StrBlobPtr& p)
        : ptr(new StrBlobPtr(p))
        { }
    StrBlobPtrPtr(const StrBlobPtrPtr& p)
        : ptr(new StrBlobPtr(*p))
        { }
    StrBlobPtrPtr(StrBlobPtrPtr&& p) noexcept
        : ptr(p.ptr)
        { p.ptr = nullptr; }
    ~StrBlobPtrPtr()
        { delete ptr; }
    StrBlobPtrPtr& operator=(const StrBlobPtrPtr rhs);
    StrBlobPtrPtr& operator=(StrBlobPtrPtr&& rhs) noexcept;

    StrBlobPtr& operator*() const
        { return *ptr; }
    StrBlobPtr* operator->() const
        { return ptr; }

friend void swap(StrBlobPtrPtr& lhs, StrBlobPtrPtr& rhs);

private:
    StrBlobPtr* ptr;
};


inline StrBlobPtrPtr& StrBlobPtrPtr::operator=(const StrBlobPtrPtr rhs)
{
    StrBlobPtr* p = new StrBlobPtr(*rhs.ptr);
    delete ptr;
    ptr = p;
    return *this;
}

inline StrBlobPtrPtr& StrBlobPtrPtr::operator=(StrBlobPtrPtr&& rhs) noexcept
{
    if(this == &rhs)
        return *this;
    delete ptr;
    ptr = rhs.ptr;
    rhs.ptr = nullptr;
    return *this;
}

inline void swap(StrBlobPtrPtr& lhs, StrBlobPtrPtr& rhs)
{
    using std::swap;
    swap(lhs.ptr, rhs.ptr);
}


#endif /*STRBLOBPTRPTR_H_*/
