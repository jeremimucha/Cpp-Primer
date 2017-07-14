// strvec.h -- Chapter 13 - Classes that manage dynamic memory
#ifndef STRVEC_H_
#define STRVEC_H_

#include <string>
#include <memory>
#include <utility>
#include <initializer_list>
#include <algorithm>


// simplified implementation of the memory allocation strategy for a vector-like class
class StrVec
{
public:
    StrVec()       // the allocator member is default initialized
        : elements(nullptr), first_free(nullptr), cap(nullptr)
        { }
    StrVec(const StrVec&);              // copy ctor
    StrVec(const std::initializer_list<std::string> il);
    StrVec(StrVec&& s) noexcept
        // member initializers take over the resources in s
        : elements(s.elements), first_free(s.first_free), cap(s.cap)
        {
            // leave s in a state in which it is safe to run the destructor
            s.elements = s.first_free = s.cap = nullptr;
        }
    ~StrVec();                          // destructor
    StrVec& operator=(const StrVec&);       // copy assignment
    StrVec& operator=(StrVec&&) noexcept;   // move assignment
    StrVec& operator=(std::initializer_list<std::string> il);

    void push_back(const std::string&); // copy the element
    void push_back(std::string&&);
    
    size_t size() const
        { return first_free - elements; }
    size_t capacity() const 
        { return cap - elements; }
    
    void reserve(std::size_t n);
    void resize(std::size_t n, const std::string& s);
    
    std::string* begin() const
        { return elements; }
    std::string* end() const
        { return first_free; }
    
    std::string& operator[](std::size_t n)
        { return elements[n]; }
    const std::string& operator[](std::size_t n) const
        { return elements[n]; }

private:
    std::allocator<std::string> alloc; // allocates the elements
    
    // used by the functions that add elements to the StrVec
    void chk_n_alloc()
        { if( size() == capacity()) reallocate(); }

// utilities used by the copy constructor, assignment and destructor
    std::pair<std::string*, std::string*>
        alloc_n_copy(const std::string*, const std::string*);
    
    void free();        // destroy the elements and free the space
    void reallocate();  // get more space and copy the existing elements
    
    std::string* elements;      // pointer to the first element in the array
    std::string* first_free;    // pointer to the first free element in the array
    std::string* cap;           // pointer to the one past the end of the array
};


inline void StrVec::push_back(const std::string& s)
{
    chk_n_alloc();  // ensure that there is room for another element
    // construct a copy of s in the element to which first_free points
    alloc.construct(first_free++, s);
}

inline void StrVec::push_back(std::string&& s)
{
    chk_n_alloc();  // reallocates the StrVec if necessary
    alloc.construct(first_free++, std::move(s));
}

inline std::pair<std::string*, std::string*>
StrVec::alloc_n_copy(const std::string* b, const std::string* e)
{
    // allocate space to hold as many elements as are in the range
    std::string* data = alloc.allocate(e - b);
    // initialize and return a pair constructed from data and
    // the value returned by uninitialized_copy
    return {data, std::uninitialized_copy(b, e, data)};
}

inline void StrVec::free()
{
    // may not pass deallocate a 0 pointer; if elements is 0, there's no work to do
    if(elements){
        // destroy the old elements in reverse order
        for(std::string* p = first_free; p != elements; /*empty*/)
            alloc.destroy(--p);
        // deallocate the memory
        alloc.deallocate(elements, cap - elements);
    }
}


inline StrVec::StrVec(const StrVec& rhs)
{
    // call alloc_n_copy to allocate exactly as many elements as in s
    std::pair<std::string*,std::string*> data = alloc_n_copy(rhs.begin(), rhs.end());
    elements = data.first;
    first_free = cap = data.second;
}

inline StrVec::StrVec(const std::initializer_list<std::string> il)
{
    // call alloc_n_copy to allocate exactly as many elements as in il
    std::pair<std::string*,std::string*> data = alloc_n_copy(il.begin(), il.end());
    elements = data.first;
    first_free = cap = data.second;
}

inline StrVec& StrVec::operator=(StrVec&& rhs) noexcept
{
    if(this != &rhs){
        free();                         // free existing elements;
        elements = rhs.elements;        // take over resources from rhs
        first_free = rhs.first_free;
        cap = rhs.cap;
        // leave rhs in a destructible state
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

inline StrVec::~StrVec()
{
    free();
}


#endif /*STRVEC_H_*/
