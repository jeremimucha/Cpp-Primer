/* Exercise 19.1: Write your own  operator new(size_t) function using  malloc
and use  free to write the  operator delete(void*) function. */
#include <iostream>
#include <cstdlib>
#include <stdexcept>


void* operator new(size_t);     // allocate an object
void* operator new[](size_t);   // allocate an array
void operator delete(void*) noexcept;      // free an object
void operator delete[](void*) noexcept;    // free an array
void operator delete(void*, size_t) noexcept;
void operator delete[](void*, size_t) noexcept;

int main()
{
    int* pi = new int;
    delete pi;

    int* pai = new int[10];
    delete[] pai;

    std::cerr << "\nDone";
}


void* operator new(size_t size)
{
    if( void* mem = malloc(size) ){
        std::cerr << "operator new: allocating " << size
                  << " bytes at address "
                  << reinterpret_cast<const void*>(mem) << std::endl;
        return mem;
    }
    else
        throw std::bad_alloc();
}

void* operator new[](size_t size)
{
    if( void* mem = malloc(size) ){
        std::cerr << "operator new[]: allocating " << size
                  << " bytes at address "
                  << reinterpret_cast<const void*>(mem) << std::endl;
        return mem;
    }
    else
        throw std::bad_alloc();
}

void operator delete(void* mem) noexcept
{
    std::cerr << "operator delete: freeing memory at address "
              << reinterpret_cast<const void*>(mem) << std::endl;
    free(mem);
}

void operator delete[](void* mem) noexcept
{
    std::cerr << "operator delete[]: freeing memory at address " << mem << std::endl;
            //   << reinterpret_cast<const void*>(mem) << std::endl;
    free(mem);
}

void operator delete(void* mem, size_t) noexcept
{
    std::cerr << "operator delete(void*,size_t): freeing memory at address "
              << mem << std::endl;
    free(mem);
}

void operator delete[](void* mem, size_t) noexcept
{
    std::cerr << "operator delete[](void*,size_t): freeing memory at address "
              << mem << std::endl;
    free(mem);
}
