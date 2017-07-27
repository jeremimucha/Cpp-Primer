#ifndef UNIQUEPTR_H_
#define UNIQUEPTR_H_

#include <utility>
#include <functional>


template<typename T, typename Deleter> class Uniqueptr;
template<typename T, typename D>
void swap(Uniqueptr<T,D>& lhs, Uniqueptr<T,D>& rhs) noexcept;
template<typename T, typename D>
bool operator==(const Uniqueptr<T,D>& lhs, const Uniqueptr<T,D>& rhs) noexcept;
template<typename T, typename D>
bool operator!=(const Uniqueptr<T,D>& lhs, const Uniqueptr<T,D>& rhs) noexcept;
template<typename T, typename D>
bool operator<(const Uniqueptr<T,D>& lhs, const Uniqueptr<T,D>& rhs) noexcept;
template<typename T, typename D>
bool operator<=(const Uniqueptr<T,D>& lhs, const Uniqueptr<T,D>& rhs) noexcept;
template<typename T, typename D>
bool operator>(const Uniqueptr<T,D>& lhs, const Uniqueptr<T,D>& rhs) noexcept;
template<typename T, typename D>
bool operator>=(const Uniqueptr<T,D>& lhs, const Uniqueptr<T,D>& rhs) noexcept;


template<typename T, typename Deleter=void(*)(T*)>
class Uniqueptr
{
public:
    constexpr Uniqueptr() noexcept
        : p(nullptr), del(nullptr)
        { }
    constexpr Uniqueptr(std::nullptr_t np) noexcept
        : p(np), del(nullptr)
        { }
    explicit Uniqueptr(T* ptr) noexcept
        : p(ptr), del(nullptr)
        { }
    Uniqueptr(T* ptr, Deleter deleter)
        : p(ptr), del(deleter)
        { }
    Uniqueptr(const Uniqueptr&) = delete;
    Uniqueptr(Uniqueptr&& u) noexcept
        : p(std::move(u.p)), del(std::move(u.del))
        {
            u.p = nullptr; u.del = nullptr;
        }
    Uniqueptr& operator=(const Uniqueptr& u) = delete;
    Uniqueptr& operator=(Uniqueptr&& u) noexcept;
    Uniqueptr& operator=(std::nullptr_t np) noexcept;
    ~Uniqueptr() noexcept
    {
        if(del)
            del(p);
        else
            delete p;
        // del = nullptr;
    }
    T* release() noexcept
        {
            T* ret = std::move(p);
            p = nullptr;
            // del = nullptr;
            return ret;
        }
    void reset(T* ptr) noexcept
        {
            T* old = std::move(p);
            p = ptr;
            if(old && del)
                del(old);
            else
                delete old;
        }
    T* get() const noexcept
        { return p; }
    Deleter& get_deleter() noexcept
        { return del; }
    const Deleter& get_deleter() const noexcept
        { return del; }

    explicit operator bool() const noexcept
        { return p != nullptr; }

    T& operator*() const noexcept
        { return *p; }
    T* operator->() const noexcept
        { return p; }

    friend void swap<T,Deleter>(Uniqueptr& lhs, Uniqueptr& rhs) noexcept;
    friend bool operator== <T,Deleter>(const Uniqueptr& lhs, const Uniqueptr& rhs) noexcept;
    friend bool operator!= <T,Deleter>(const Uniqueptr& lhs, const Uniqueptr& rhs) noexcept;
    friend bool operator< <T,Deleter>(const Uniqueptr& lhs, const Uniqueptr& rhs) noexcept;
    friend bool operator<= <T,Deleter>(const Uniqueptr& lhs, const Uniqueptr& rhs) noexcept;
    friend bool operator> <T,Deleter>(const Uniqueptr& lhs, const Uniqueptr& rhs) noexcept;
    friend bool operator>= <T,Deleter>(const Uniqueptr& lhs, const Uniqueptr& rhs) noexcept;
private:
    T* p;
    Deleter del;
};


template<typename T, typename Deleter>
Uniqueptr<T,Deleter>& Uniqueptr<T,Deleter>::operator=(Uniqueptr&& rhs) noexcept
{
    if(this == &rhs)
        return *this;
    if(del)
        del(p);
    else
        delete p;
    p = std::move(rhs.p);
    del = std::move(rhs.del);
    return *this;
}

template<typename T, typename Deleter>
Uniqueptr<T,Deleter>& Uniqueptr<T,Deleter>::operator=(std::nullptr_t np) noexcept
{
    if(del)
        del(p);
    else
        delete p;
    p = np;
    del = np;
    return *this;
}

template<typename T, typename D>
inline void swap(Uniqueptr<T,D>& lhs, Uniqueptr<T,D>& rhs) noexcept
{
    using std::swap;
    swap(lhs.p, rhs.p);
    swap(lhs.del, rhs.del);
}

template<typename T, typename D>
inline bool operator==(const Uniqueptr<T,D>& lhs, const Uniqueptr<T,D>& rhs) noexcept
{ return lhs.p == rhs.p; }

template<typename T, typename D>
inline bool operator!=(const Uniqueptr<T,D>& lhs, const Uniqueptr<T,D>& rhs) noexcept
{ return !(lhs == rhs); }

template<typename T, typename D>
inline bool operator<(const Uniqueptr<T,D>& lhs, const Uniqueptr<T,D>& rhs) noexcept
{ return std::less<T>(lhs.p, rhs.p); }

template<typename T, typename D>
inline bool operator<=(const Uniqueptr<T,D>& lhs, const Uniqueptr<T,D>& rhs) noexcept
{ return !(rhs < lhs); }

template<typename T, typename D>
inline bool operator>(const Uniqueptr<T,D>& lhs, const Uniqueptr<T,D>& rhs) noexcept
{ return rhs < lhs; }

template<typename T, typename D>
inline bool operator>=(const Uniqueptr<T,D>& lhs, const Uniqueptr<T,D>& rhs) noexcept
{ return !(lhs < rhs); }

#endif /* UNIQUEPTR_H_ */
