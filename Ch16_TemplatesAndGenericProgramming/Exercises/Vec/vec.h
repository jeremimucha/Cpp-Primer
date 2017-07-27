#ifndef VEC_H_
#define VEC_H_


#include <memory>
#include <utility>
#include <initializer_list>
#include <algorithm>
#include <iterator>


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
    template<typename... Args>
    void emplace_back(Args&&...);

    size_type size() const
        { return first_free - elements; }
    size_type capacity() const
        { return cap - elements; }

    void reserve(size_type n);
    void resize(size_type n, const T& t=T());

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
// --- member variables
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
template<typename... Args>
inline void Vec<T>::emplace_back(Args&&... args)
{
    chk_n_alloc();  // reallocate if necessary
    alloc.construct(first_free++, std::forward<Args>(args)...);
}

template<typename T>
inline std::pair<T*,T*> Vec<T>::alloc_n_copy(const T* b,  const T* e)
{
    // allocate space to hold as many elements as are in the range
    T* data = alloc.allocate(e - b);
    // initialize and return a pair constructed from data and
    // the value returned by uninitialized_copy
    return {data, std::uninitialized_copy(b, e, data) };

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

template<typename T>
void Vec<T>::reserve(size_type n)
{
    if(n <= capacity() )
        return;
    
    T* first = alloc.allocate(n);
    T* last = std::uninitialized_copy(std::make_move_iterator(begin())
                                     ,std::make_move_iterator(end())
                                     ,first);
    free();
    elements = first;
    first_free = last;
    cap = elements + n;
}

template<typename T>
inline void Vec<T>::reallocate()
{
    // allocate space for twice as many elements as the current size
    size_type newcapacity = size() ? 2*size() : 1;
    reserve(newcapacity);
    // T* first = alloc.allocate(newcapacity);
    // // move the elements using the move_iterator adaptor
    // T* last = std::uninitialized_copy(std::make_move_iterator(begin())
    //                                  ,std::make_move_iterator(end())
    //                                  ,first);
    // free();     // free the old space
    // elements = first;
    // first_free = last;
    // cap = elements + newcapacity;
}

template<typename T>
void Vec<T>::resize(size_type n, const T& t)
{
    if(n < size()){
        for( T* newend = elements + n; first_free != newend; /**/ )
            alloc.destroy(--first_free);
        return;
    }

    if(n > capacity())
        reserve(n);
    first_free = std::uninitialized_fill_n(first_free
                                          ,((elements+n) - first_free)
                                          ,t);
}

template<typename T>
inline Vec<T>::Vec(const Vec<T>& v)
{
    // call alloc_n_copy to allocate exactly as many elements as in v
    std::pair<T*,T*> data = alloc_n_copy(v.cbegin(), v.cend());
    elements = data.first;
    first_free = cap = data.second;
}

template<typename T>
inline Vec<T>::Vec(const std::initializer_list<T> il)
{
    std::pair<T*,T*> data = alloc_n_copy(il.begin(), il.end());
    elements = data.first;
    cap = first_free = data.second;
}

template<typename T>
Vec<T>& Vec<T>::operator=(const Vec<T>& rhs)
{
    if(this == &rhs)
        return *this;
    // call alloc_n_copy to allocate exactly as many elements as in rhs
    std::pair<T*,T*> data = alloc_n_copy(rhs.cbegin(), rhs.cend());
    free();
    elements = data.first;
    cap = first_free = data.second;
    return *this;
}

template<typename T>
inline Vec<T>& Vec<T>::operator=(Vec<T>&& rhs) noexcept
{
    if(this != &rhs){
        free();                 // free existing elements
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        // leave rhs in a destructible state
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

template<typename T>
inline Vec<T>& Vec<T>::operator=(std::initializer_list<T> il)
{
    std::pair<T*,T*> data = alloc_n_copy(il.begin(), il.end());
    free();
    elements = data.first;
    cap = first_free = data.second;
    return *this;
}

template<typename T>
inline Vec<T>::~Vec<T>()
{
    free();
}



#endif /* VEC_H_ */
