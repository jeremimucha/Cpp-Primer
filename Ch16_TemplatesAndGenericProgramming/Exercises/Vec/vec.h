#ifndef VEC_H_
#define VEC_H_


#include <memory>
#include <utility>
#include <initializer_list>
#include <algorithm>


template<typename T>
class Vec
{
public:
    using size_type = std::size_t;
    Vec()
        : elements(nullptr), first_free(nullptr), cap(nullptr)
        { }
    Vec(const std::initializer_list<T> il);
    Vec(const Vec&);
    Vec(Vec&& v) noexcept
        : elements(v.elements), first_free(v.first_free), cap(v.cap)
        {
            v.elements = v.first_free = v.cap = nullptr;
        }
    ~Vec(); // destructor
    Vec& operator=(const Vec&);
    Vec& operator=(Vec&&) noexcept;
    Vec& operator=(std::initializer_list<T> il);

    void push_back(const T&);
    void push_back(T&&);

    size_type size() const
        { return first_free - elements; }
    size_type capacity() const
        { return cap - elements; }

    void reserve(size_type n);
    void resize(size_type n, const T&);

    T* begin()
        { return elements; }
    T* end()
        { return first_free; }
    const T* cbegin() const
        { return elements; }
    const T* cend() const
        { return first_free; }

    T& operator[](size_type n)
        { return elements[n]; }
    const T& operator[](size_type n) const
        { return elements[n]; }
    
private:
    std::allocator<T> alloc;    // allocates the elements

// used by the functions that add elements to the StrVec
    void chk_n_alloc()
        { if( size() == capacity() ) reallocate(); }

// utilities used by the copy constructor, assignment and destructor
    std::pair<T*, T*> alloc_n_copy(const T*, const T*);
    void free();        // destroy the elements and free the space
    void reallocate();  // get more space and copy the existing elements

    T* elements;        // pointer to the first element in the array
    T* first_free;      // pointer to the first free element in the array
    T* cap;             // pointer to the one past the end of the array
};


template<typename T>
inline void Vec<T>::push_back(const T& t)
{
    chk_n_alloc();
    // construct a copy of s in the element to which first_free points
    alloc.construct(first_free++, t);
}

template<typename T>
inline void Vec<T>::push_back(T&& t)
{
    chk_n_alloc();
    alloc.construct(first_free++, std::move(t));
}

template<typename T>
inline std::pair<T*,T*> Vec<T>::alloc_n_copy(const T* b,  const T* e)
{
    // allocate space to hold as many elements as are in the range
    T* data = alloc.allocate(e - b);
    // initialize and return a pair constructed from data and
    // the value returned by uninitialized_copy
    return {data, std::uninitialized_copy(b, e, data); }

}

template<typename T>
inline void Vec<T>::free()
{
    // may not pass deallocate a nullptr; if elements is nullptr there's no work to do
    if(elements){
        // destroy the old elements in reverse order
        for(T* p=first_free; p != elements; )
            alloc.destroy(--p);
        // deallocate the memory
        alloc.deallocate(elements, cap-elements);
    }
}

#endif /* VEC_H_ */
