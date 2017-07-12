#include "strvec.h"


StrVec& StrVec::operator=(const StrVec& rhs)
{
    // call alloc_n_copy to allocate exactly as many elements as in rhs
    std::pair<std::string*,std::string*> data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

void StrVec::reallocate()
{
    // we'll allocate space for twice as many elements as the current size
    std::size_t newcapacity = size() ? 2*size() : 1;
    // allocate new memory
    std::string* newdata = alloc.allocate(newcapacity);
    // move the data from the old memory to the new
    std::string* dest = newdata;    // points to the next free position in the new array
    std::string* elem = elements;   // points to the next element in the old array
    for(std::size_t i=0; i!=size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free(); // free the old space once we've moved the elements
    // update our data structure to point to the new elements
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

void StrVec::reserve(std::size_t n=0)
{
    if( n <= capacity() )
        return;

    std::string* newdata = alloc.allocate(n);
    std::string* dst = newdata;
    std::string* elem = elements;
// construct the objects in the new memory
    for(std::size_t i=0; i!=size(); ++i)
        alloc.construct(dst++, std::move(*elem++));
// destroy and free the old address space
    free();

    elements = newdata;
    first_free = dst;
    cap = elements + n;
}

void StrVec::resize(std::size_t n, const std::string& s="")
{
    if(n < size()){
        for( std::string* newend = elements+n; first_free != newend; )
            alloc.destroy(--first_free);
        return;
    }

    if(n > capacity())
        reserve(n);
    for(std::string* newend = elements+n; first_free != newend; )
        alloc.construct(first_free++, s);
}

