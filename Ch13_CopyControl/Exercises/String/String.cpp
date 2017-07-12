#include "String.h"
#include <utility>
#include <cstring>


void String::reserve(size_type n)
{
    if( n <= capacity() )
        return;
    
    char* newelems = alloc.allocate(++n);
    char* dst = newelems;
// construct the objects in new memory
    for(char* elem = elements; elem != first_free;)
        alloc.construct(dst++, std::move(*elem++));
    alloc.construct(dst+1, '\0');
// destroy and free old data
    free();

    elements = newelems;
    first_free = dst;
    cap = elements + n - 1; // point to the last element, rather than one beyond
}


void String::resize(size_type n, char c)
{
    if( n < size() ){
        shrink(n);
        return;
    }

    if( n > capacity() )
        reserve(n);
    for(char* newend = elements+n; first_free != newend; )
        alloc.construct(first_free++, c);
    alloc.construct(first_free+1, '\0');
}


// constructors
/* ------------------------------------------------------------------------- */
String::String(unsigned int n, char c)
    : elements(alloc.allocate(n+1))
    , first_free(std::uninitialized_fill_n(elements, n, c))
    , cap(elements+n)
{
    alloc.construct(first_free+1,'\0');
}

String::String(const char* cstr)
{
    size_type len = std::strlen(cstr);
    elements = alloc.allocate(len+1);
    first_free = std::uninitialized_copy(cstr, cstr+len, elements);
    alloc.construct(first_free+1, '\0');
    cap = elements + len;
}

String::String(const char* b, const char* e)
{
    std::pair<char*,char*> data = alloc_n_copy(b, e);
    elements = data.first;
    cap = first_free = data.second;
}

String::String(const String& rhs)
{
    std::pair<char*,char*> data = alloc_n_copy(rhs.cbegin(), rhs.cend());
    elements = data.first;
    cap = first_free = data.second;
}

String& String::operator=(const String& rhs)
{
    std::pair<char*,char*> data = alloc_n_copy(rhs.cbegin(), rhs.cend());
    free();
    elements = data.first;
    cap = first_free = data.second;
    return *this;
}

/* ------------------------------------------------------------------------- */

// modifiers
/* ------------------------------------------------------------------------- */
String& String::append(const String& s)
{
    // reserve(size() + s.size());
    // first_free = uninitialized_copy(s.cbegin(), s.cend(), first_free);
    // return *this;
    return append(s.cbegin(), s.cend());
}

String& String::append(const char* s)
{
    size_type len = std::strlen(s);
    // reserve(size() + s.size());
    // first_free = uninitialized_copy(s.cbegin(), s.cend(), first_free);
    // return *this;
    return append(s, s+len);
}

String& String::append(const char* b, const char* e)
{
    reserve(size() + (e-b));    // reserve will allocate one additional element
    first_free = std::uninitialized_copy(b, e, first_free);
    alloc.construct(first_free, '\0');  // construct the last elem to '\0'
    return *this;
}

void String::push_back(char c)
{
    chk_n_alloc();
    alloc.construct(first_free++, c);
}
void String::pop_back()
{
    if(first_free != elements)
        alloc.destroy(--first_free);
}

/* ------------------------------------------------------------------------- */

// data access
/* ------------------------------------------------------------------------- */
const char* String::data()
{
    chk_n_alloc();
    alloc.construct(first_free+1, '\0');
    return elements;
}
/* ------------------------------------------------------------------------- */