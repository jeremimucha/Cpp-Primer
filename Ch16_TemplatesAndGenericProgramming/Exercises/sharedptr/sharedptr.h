#ifndef SHAREDPTR_H_
#define SHAREDPTR_H_

#include <functional>


template<typename T>
class Sharedptr
{
public:
    Sharedptr()
        : p(nullptr), use(nullptr), del(dd)
        { }
    Sharedptr(T* ptr, std::function<void(T*)> deleter=dd)
        : p(ptr), use( new std::size_t(1) ), del(deleter)
        { }
    Sharedptr(const Sharedptr& sp) noexcept
        : p(sp.p), use(sp.use), del(sp.del)
        { ++*use; }
    Sharedptr(Sharedptr&& sp) noexcept
        : p(std::move(sp.p)), use(std::move(sp.use), del(std::move(sp.del)))
        { sp.p = nullptr; sp.use = nullptr; sp.del = nullptr; }
    Sharedptr& operator=(const Sharedptr&);
    Sharedptr& operator=(Sharedptr&&) noexcept;
private:
    T* p;
    std::size_t* use;
    std::function<void(T*)> del;

    static inline void dd(T* p){ delete p; }
};


inline Sharedptr& Sharedptr::operator=(const Sharedptr& rhs)
{
    // protect against self-assignment by incrementing the use count first
    ++*rhs.use;
    if(--*use == 0){
        delete p;
        delete use;
    }
    p = rhs.p;
    use = rhs.use;
    del = rhs.del;
    return *this;
}

inline Sharedptr& Sharedptr::operator=(Sharedptr&& rhs) noexcept
{
    if(this == &rhs)
        return *this;
    if( --*use == 0 ){
        delete p;
        delete use;
    }
    p = std::move(rhs.p);
    use = std::move(rhs.use);
    rhs.p = nullptr;
    rhs.use = nullptr;
    rhs.del = nullptr;
    return *this;
}


#endif /* SHAREDPTR_H_ */
