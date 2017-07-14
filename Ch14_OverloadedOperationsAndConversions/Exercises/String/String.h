// String.h -- Chapter 13 -- Copy Control
// a simplified string class
#ifndef STRING_H_
#define STRING_H_

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <initializer_list>


// simplified implementation of the memory allocation strategy for a string-like class
class String
{
public:
// public types
/* ------------------------------------------------------------------------- */
    using size_type      = std::size_t;
    using iterator       = char*;
    using const_iterator = const char*;
/* ------------------------------------------------------------------------- */

// constructor / destructors
/* ------------------------------------------------------------------------- */
    String()
        : elements(nullptr), first_free(nullptr), cap(nullptr)
        { }
    String(unsigned int n, char c);
    String(const char* cstr);
    String(const char* b, const char* e);
    String(const String&);
    String(String&&) noexcept;
    String& operator=(const String&);
    String& operator=(String&&) noexcept;
    ~String();
/* ------------------------------------------------------------------------- */

// capacity
/* ------------------------------------------------------------------------- */
    size_type size() const noexcept
        { return first_free - elements; }
    size_type length() const noexcept
        { return size(); }
    size_type capacity() const noexcept
        { return cap - elements; }
    void reserve(size_type n=0);
    void resize(size_type n, char c);
    void resize(size_type n);
/* ------------------------------------------------------------------------- */

// element access
/* ------------------------------------------------------------------------- */
    char& operator[](size_type n) noexcept
        { return elements[n]; }
    const char& operator[](size_type n) const noexcept
        { return elements[n]; }
    char& back() noexcept
        { return *(first_free-1); }
    const char& back() const noexcept
        { return *(first_free-1); }
    char& front() noexcept
        { return *elements; }
    const char& front() const noexcept
        { return *elements; }
    const char* data() const noexcept
        { return elements; }
    const char* c_str() const noexcept
        { return data(); }

    char* begin() noexcept
        { return elements; }
    char* end() noexcept
        { return first_free; }
    const char* cbegin() const noexcept
        { return elements; }
    const char* cend() const noexcept
        { return first_free; }
/* ------------------------------------------------------------------------- */

// modifiers
/* ------------------------------------------------------------------------- */
    String& append(const String& s);
    String& append(const char* s);
    String& append(const char* b, const char* e);
    void push_back(char c);
    void pop_back();
    void swap(String& s);
/* ------------------------------------------------------------------------- */

// friends
/* ------------------------------------------------------------------------- */
    friend void swap(String& lhs, String& rhs);
    friend std::ostream& operator<<(std::ostream& os, const String& s);
    friend bool operator==(const String& lhs, const String& rhs);
    friend bool operator!=(const String& lhs, const String& rhs);
    friend bool operator<(const String& lhs, const String& rhs);
/* ------------------------------------------------------------------------- */


private:
// memory allocation
    std::allocator<char> alloc;

// utilities used by the ctor, assignment, and dtor
/* ------------------------------------------------------------------------- */
    void chk_n_alloc()
        { if(first_free == cap) reserve(2*capacity()); }

    std::pair<char*,char*> alloc_n_copy(const char* b, const char* e)
        {
            char* elems = alloc.allocate((e - b) + 1);
            char* last = std::uninitialized_copy(b, e, elems);  // returns one-past last elem
            alloc.construct(last, '\0');    // cap will point to last rather than one past the last elem
            return {elems, last};
        }

    void free();

    // void reallocate();

    void shrink(size_type n);
/* ------------------------------------------------------------------------- */

// members
/* ------------------------------------------------------------------------- */
    char* elements;
    char* first_free;
    char* cap;
/* ------------------------------------------------------------------------- */
};


inline void String::free()
{
    if(elements){
        // destroy the first_free element - constructed to = '\0'
        for(char* p=first_free; p!=elements; --p)
            alloc.destroy(p);
        alloc.deallocate(elements, capacity());
    }
}

inline void String::shrink(size_type n)
{
    for(char* newend = elements+n; first_free != newend; ){
        alloc.destroy(--first_free);
        alloc.construct(first_free, '\0');
    }
}

inline String::~String()
{
    free();
}


inline void String::swap(String& s)
{
    using std::swap;
    swap(elements, s.elements);
    swap(first_free, s.first_free);
    swap(cap, s.cap);
}

inline void swap(String& lhs, String& rhs)
{
    using std::swap;
    swap(lhs.elements, rhs.elements);
    swap(lhs.first_free, rhs.first_free);
    swap(lhs.cap, rhs.cap);
}

inline std::ostream& operator<<(std::ostream& os, const String& s)
{
    return os << s.data();
}

inline
bool operator==(const String& lhs, const String& rhs)
{
    const char* pl=lhs.cbegin();
    const char* pr=rhs.cbegin();
    while(pl != lhs.cend() && pr!=rhs.cend())
        if(*pl++ != *pr++) return false;
    return *pl == *pr;
}

inline
bool operator!=(const String& lhs, const String& rhs)
{
    return !(lhs == rhs);
}

inline
bool operator<(const String& lhs, const String& rhs)
{
    const char* pl = lhs.cbegin();
    const char* pr = rhs.cbegin();
    while(pl!=lhs.cend() && rl!=rhs.cend() && *pl == *rl){
        ++pl; ++rl;
    }
    return (pl==lhs.cend() && rl!=rhs.cend() || *pl < *rl);
}

#endif /*STRING_H_*/
