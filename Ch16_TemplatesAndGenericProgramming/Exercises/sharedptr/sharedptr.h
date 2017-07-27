#ifndef SHAREDPTR_H_
#define SHAREDPTR_H_

#include <functional>
#include <utility>

template<typename T> class Sharedptr;

template<typename T>void swap(Sharedptr<T>& lhs, Sharedptr<T>& rhs) noexcept;
template<typename T>bool operator==(const Sharedptr<T>& lhs, const Sharedptr<T>& rhs) noexcept;
template<typename T>bool operator!=(const Sharedptr<T>& lhs, const Sharedptr<T>& rhs) noexcept;
template<typename T>bool operator<(const Sharedptr<T>& lhs, const Sharedptr<T>& rhs) noexcept;
template<typename T>bool operator<=(const Sharedptr<T>& lhs, const Sharedptr<T>& rhs) noexcept;
template<typename T>bool operator>(const Sharedptr<T>& lhs, const Sharedptr<T>& rhs) noexcept;
template<typename T>bool operator>=(const Sharedptr<T>& lhs, const Sharedptr<T>& rhs) noexcept;


template<typename T>
class Sharedptr
{
public:
    Sharedptr()
        : p(nullptr), use(nullptr), del(dd)
        { }
    // explicit Sharedptr(T* ptr)
    //     : p(ptr), use( new std::size_t(1) ), del(dd)
    //     { }
    template< typename Deleter=std::function<void(T*)> >
    explicit Sharedptr(T* ptr, Deleter deleter = dd)
        : p(ptr), use( new std::size_t(1) ), del(deleter)
        { }
    Sharedptr(const Sharedptr& sp) noexcept
        : p(sp.p), use(sp.use), del(sp.del)
        { if(use) ++*use; }
    Sharedptr(Sharedptr&& sp) noexcept
        : p(std::move(sp.p)), use(std::move(sp.use)), del(std::move(sp.del))
        { sp.p = nullptr; sp.use = nullptr; sp.del = dd; }
    Sharedptr& operator=(const Sharedptr&);
    Sharedptr& operator=(Sharedptr&&) noexcept;
    ~Sharedptr() noexcept;
    void reset() noexcept;  //
    template<typename Y> void reset(Y* ptr);
    template<typename Y, typename Deleter> void reset(Y* ptr, Deleter deleter);

    T* get() noexcept
        { return p; }
    T& operator*() const noexcept
        { return *p; }
    T* operator->() const noexcept
        { return p; }
    
    std::size_t use_count() const noexcept
        { return (use ? *use : 0); }
    bool unique() const noexcept
        { return (use ? (*use==1) : 0); }
    explicit operator bool() const noexcept
        { return p != nullptr; }

    friend void swap<T>(Sharedptr<T>& lhs, Sharedptr<T>& rhs) noexcept;
    friend bool operator== <T>(const Sharedptr& lhs, const Sharedptr& rhs) noexcept;
    friend bool operator!= <T>(const Sharedptr& lhs, const Sharedptr& rhs) noexcept;
    friend bool operator< <T>(const Sharedptr& lhs, const Sharedptr& rhs) noexcept;
    friend bool operator<= <T>(const Sharedptr& lhs, const Sharedptr& rhs) noexcept;
    friend bool operator> <T>(const Sharedptr& lhs, const Sharedptr& rhs) noexcept;
    friend bool operator>= <T>(const Sharedptr& lhs, const Sharedptr& rhs) noexcept;
private:
    T* p;
    std::size_t* use;
    std::function<void(T*)> del;

    static inline void dd(T* p){ delete p; }
};

template<typename T>
inline Sharedptr<T>& Sharedptr<T>::operator=(const Sharedptr& rhs)
{
    if(this == &rhs)
        return *this;

    if(use && --*use == 0){
        del(p);
        delete use;
    }
    p = rhs.p;
    use = rhs.use;
    ++*use;
    del = rhs.del;
    return *this;
}

template<typename T>
inline Sharedptr<T>& Sharedptr<T>::operator=(Sharedptr&& rhs) noexcept
{
    if(this == &rhs)
        return *this;
    if(use && --*use == 0){
        del(p);
        delete use;
    }
    p = std::move(rhs.p);
    use = std::move(rhs.use);
    del = std::move(rhs.del);
    rhs.p = nullptr;
    rhs.use = nullptr;
    rhs.del = dd;
    return *this;
}

template<typename T>
inline Sharedptr<T>::~Sharedptr() noexcept
{
    if(use && --*use == 0){
        del(p);
        delete use;
    }
}

template<typename T>
inline void swap(Sharedptr<T>& lhs, Sharedptr<T>& rhs) noexcept
{
    using std::swap;
    swap(lhs.p, rhs.p);
    swap(lhs.use, rhs.use);
    swap(lhs.del, rhs.del);
}

template<typename T>
void Sharedptr<T>::reset() noexcept
{
    if(use && --*use == 0 ){
        del(p);
        delete use;
    }
    p = nullptr;
    use = nullptr;
    del = dd;
}

template<typename T>
template<typename Y>
void Sharedptr<T>::reset(Y* ptr)
{
    if(use && --*use == 0 ){
        del(p);
        delete use;
    }
    p = ptr;
    use = new std::size_t(1);
    // del = dd;
}

template<typename T>
template<typename Y, typename Deleter>
void Sharedptr<T>::reset(Y* ptr, Deleter deleter)
{
    if(use && --*use == 0 ){
        del(p);
        delete use;
    }
    p = ptr;
    use = new std::size_t(1);
    del = deleter;
}


template<typename T>
inline bool operator==(const Sharedptr<T>& lhs, const Sharedptr<T>& rhs) noexcept
{ return lhs.p == rhs.p; }

template<typename T>
bool operator!=(const Sharedptr<T>& lhs, const Sharedptr<T>& rhs) noexcept
{ return !(lhs == rhs); }

template<typename T>
bool operator<(const Sharedptr<T>& lhs, const Sharedptr<T>& rhs) noexcept
{ return std::less<T>(lhs.p, rhs.p); }

template<typename T>
bool operator<=(const Sharedptr<T>& lhs, const Sharedptr<T>& rhs) noexcept
{ return !(rhs < lhs); }

template<typename T>
bool operator>(const Sharedptr<T>& lhs, const Sharedptr<T>& rhs) noexcept
{ return rhs < lhs; }

template<typename T>
bool operator>=(const Sharedptr<T>& lhs, const Sharedptr<T>& rhs) noexcept
{ return !(lhs < rhs); }


#endif /* SHAREDPTR_H_ */
