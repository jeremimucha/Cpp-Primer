#ifndef BLOBPTR_H_
#define BLOBPTR_H_

#include "blob.h"


template<typename T>
class BlobPtr
{
public:
    BlobPtr()
        : curr(0)
        { }
    BlobPtr(Blob<T>& a, size_t sz=0)
        : wptr(a.data), curr(sz)
        { }
    T& operator*() const
    {
        std::shared_ptr<std::vector<T>> p = check(curr, "dereference past end");
        return (*p)[curr];      // (*p) is the vecto to which this obj points
    }
    T* operator->() const
    {
        return &(this->operator*());
    }
    // increment and decrement
    BlobPtr& operator++();      // prefix operators
    BlobPtr& operator--();
    BlobPtr operator++(int);    // postfix operators
    BlobPtr operator--(int);
    BlobPtr& operator+=(std::size_t n);
    BlobPtr operator+(std::size_t n);
    BlobPtr& operator-=(std::size_t n);
    BlobPtr operator-(std::size_t n);
    // element access
    T& operator[](std::size_t) const;

    // equality and relational operators
    bool operator==(const BlobPtr& rhs) const
        { return curr == rhs.curr; }
    bool operator!=(const BlobPtr& rhs) const
        { return !(*this == rhs); }
private:
    // check returns a shared_ptr to the vector if the check succeeds
    std::shared_ptr<std::vector<T>>
        check(std::size_t, const std::string&) const;
    // store a weak_ptr, which means the underlying vector might be destroyed
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;       // current position within the array
};


template<typename T>
std::shared_ptr<std::vector<T>>
BlobPtr<T>::check(std::size_t i, const std::string& msg) const
{
    std::shared_ptr<std::vector<T>> ret = wptr.lock();
    if( !ret )
        throw std::runtime_error("unbound BlobPtr");
    if( i >= ret->size() )
        throw std::out_of_range(msg);
    return ret;
}

template<typename T>
inline BlobPtr<T>& BlobPtr<T>::operator++()
{
    // if curr already points past the end of the container, can't increment it
    check(curr, "increment past end of BlobPtr");
    ++curr;
    return *this;
}

template<typename T>
inline BlobPtr<T>& BlobPtr<T>::operator--()
{
    // if curr is zero, decrementing it will yield an invalid subscript
    --curr;
    check(-1, "decrement past begin of BlobPtr");
    return *this;
}

// postfix: increment/decrement the object but return the unchanged value
template<typename T>
inline BlobPtr<T> BlobPtr<T>::operator++(int)
{
    // when we do not supply template arguments, the compiler assumes that
    // we are suing the same type as teh member's instantiation
    // BlobPtr<T> ret = *this is the same.
    BlobPtr ret = *this;    // save teh current value;
    // no check needed here; the call to prefix increment will do the check
    ++*this;        // advance one element; prefix ++ check the increment
    return ret;     // return the saved state
}

template<typename T>
inline BlobPtr<T> BlobPtr<T>::operator--(int)
{
    BlobPtr ret(*this); // save the current value
    --*this;    // move backward one element; prefix -- check the decrement
    return ret;
}

template<typename T>
BlobPtr<T>& BlobPtr<T>::operator+=(std::size_t n)
{
    check(curr+n, "random increment past end");
    curr += n;
    return *this;
}
template<typename T>
BlobPtr<T> BlobPtr<T>::operator+(std::size_t n)
{
    BlobPtr ret(*this);
    ret += n;
    return ret;
}
template<typename T>
BlobPtr<T>& BlobPtr<T>::operator-=(std::size_t n)
{
    curr -= n;
    check(curr, "random decrement past begin of BlobPtr");
    return *this;
}
template<typename T>
BlobPtr<T> BlobPtr<T>::operator-(std::size_t n)
{
    BlobPtr ret(*this);
    ret -= n;
    return *this;
}

template<typename T>
T& BlobPtr<T>::operator[](std::size_t n) const
{
    std::shared_ptr<std::vector<T>> p = check(curr+n, "bad index");
    if( n < 0 )
        throw std::out_of_range("bad index");
    return (*p)[curr+n];
}


#endif /* BLOBPTR_H_ */
