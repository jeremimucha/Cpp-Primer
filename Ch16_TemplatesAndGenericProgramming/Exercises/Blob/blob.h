#ifndef BLOB_H_
#define BLOB_H_

#include <vector>
#include <initializer_list>
#include <memory>
#include <stdexcept>


// forward declarations
template<typename> class BlobPtr;
template<typename> class ConstBlobPtr;
template<typename> class Blob;      // needed for parameters in operator==
template<typename T> bool operator==(const Blob<T>&, const Blob<T>&);
template<typename T> bool operator!=(const Blob<T>&, const Blob<T>&);
template<typename T> bool operator<(const Blob<T>&, const Blob<T>&);


template<typename T>
class Blob
{
// each instantiation of Blob grants access to the version of
// BlobPtr and the equality operator instantiated with the same type
    friend class BlobPtr<T>;
    friend class ConstBlobPtr<T>;
    friend bool operator==<T>(const Blob<T>&, const Blob<T>&);
    friend bool operator!=<T>(const Blob<T>&, const Blob<T>&);
    friend bool operator< <T>(const Blob<T>&, const Blob<T>&);
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    using iterator = BlobPtr<T>;
    using const_iterator = ConstBlobPtr<T>;
// constructors
    Blob();
    Blob(std::initializer_list<T> il);
    template<typename Iter>
    Blob(Iter b, Iter e)
        : data(std::make_shared<std::vector<T>>(b, e))
        { }
    
    // number of elements in the Blob
    size_type size() const
        { return data->size(); }
    bool empty() const
        { return data->empty(); }
    // add and remove elements
    void push_back(const T& t)
        { data->push_back(t); }
    // move version
    void push_back(T&& t)
        { data->push_back(std::move(t)); }
    template<typename... Args>
    void emplace_back(Args&&... args) noexcept
        { data->emplace_back(std::forward<Args>(args)...); }
    void pop_back();
    // element access
    T& back();
    const T& back() const;
    T& front();
    const T& front() const;
    T& operator[](size_type i);
    const T& operator[](size_type i) const;

    // iterators
    BlobPtr<T> begin()
        { return BlobPtr<T>(*this); }
    BlobPtr<T> end()
        { return BlobPtr<T>(*this, data->size()); }
    ConstBlobPtr<T> cbegin() const
    { return ConstBlobPtr<T>(*this); }
    ConstBlobPtr<T> cend() const
    { return ConstBlobPtr<T>(*this, data->size()); }
private:
    std::shared_ptr<std::vector<T>> data;
    // throws msg if data[i] isn't valid
    void check(size_type i, const std::string& msg) const;
};

/* Block<T> :: constructors */
/* ------------------------------------------------------------------------- */
template<typename T>
Blob<T>::Blob()
    : data(std::make_shared<std::vector<T>>())
{ }

template<typename T>
Blob<T>::Blob(std::initializer_list<T> il)
    : data(std::make_shared<std::vector<T>>(il))
{ }
/* ------------------------------------------------------------------------- */

template<typename T>
void Blob<T>::check(size_type i, const std::string& msg) const
{
    if( i >= data->size() )
        throw std::out_of_range(msg);
}

/* Blob<T> :: element access */
/* ------------------------------------------------------------------------- */
template<typename T>
T& Blob<T>::back()
{
    check(0, "back on empty Blob");
    return data->back();
}
template<typename T>
const T& Blob<T>::back() const
{
    check(0, "back on empty Blob");
    return data->back();
}

template<typename T>
T& Blob<T>::front()
{
    check(0, "front on empty Blob");
    // return data->front();
    return const_cast<T&>(front()); // ?
}

template<typename T>
const T& Blob<T>::front() const
{
    check(0, "front on empty Blob");
    return data->front();
}

template<typename T>
T& Blob<T>::operator[](size_type i)
{
    // if i is too big, check will throw, preventing access to a nonexistent element
    check(i, "subscript out of range");
    return (*data)[i];
}
template<typename T>
const T& Blob<T>::operator[](size_type i) const
{
    check(i, "subscript out of range");
    return (*data)[i];
}

template<typename T>
void Blob<T>::pop_back()
{
    check(0, "pop_back on empty Blob");
    data->pop_back();
}
/* ------------------------------------------------------------------------- */

template<typename T> bool operator==(const Blob<T>& lhs, const Blob<T>& rhs)
{
    return *lhs.data == *rhs.data;
}

template<typename T> bool operator!=(const Blob<T>& lhs, const Blob<T>& rhs)
{
    return !(lhs == rhs);
}

template<typename T> bool operator<(const Blob<T>& lhs, const Blob<T>& rhs)
{
    typename std::vector<T>::const_iterator plhs = lhs.data->cbegin();
    typename std::vector<T>::const_iterator prhs = rhs.data->cbegin();
    while(plhs != lhs.data->cend() && prhs != rhs.data->cend() && *plhs == *prhs){
        ++plhs; ++prhs;
    }
    return ( (plhs==lhs.data->cend() && prhs!=rhs.data->cend()) ||
             *plhs < *prhs );
}


#endif /* BLOB_H_ */
