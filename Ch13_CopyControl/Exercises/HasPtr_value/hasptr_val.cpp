#include "hasptr_val.h"

// void swap(HasPtr& lhs, HasPtr& rhs) noexcept
// {
//     using std::swap;
//     std::cout << "HasPtr::swap(HasPtr& lhs, HasPtr& rhs):";
//     std::cout << "\n\tlhs.ps: " << reinterpret_cast<void*>(lhs.ps)
//             << ", *lhs.ps: " << *lhs.ps << ", lhs.i: " << lhs.i;
//     std::cout << "\n\trhs.ps: " << reinterpret_cast<void*>(rhs.ps)
//             << ", *rhs.ps: " << *rhs.ps << ", rhs.i: " << rhs.i
//             << "\n";
//     swap(lhs.ps, rhs.ps);   // swap the pointers, rather than string data
//     swap(lhs.i, rhs.i);     // swap ints
// }