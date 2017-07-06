// ex 12.17
/*Which of the following  unique_ptr declarations are illegal
or likely to result in subsequent program error? Explain what the problem
is with each one.*/
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;
using std::make_unique;

int main()
{
    int ix = 1024, *pi = &ix, *pi2 = new int(2048);
    
// invalid - ix isn't a pointer
    // unique_ptr<int> p0(ix);

// legal but p1 will call delete on a non-heap object
    unique_ptr<int> p1(pi);

// legal but object pointed to by p2 and pi2 will be destroyed once p2
// goes out of scope - pi2 will be a dangling pointer
// We also now have two pointers to the same heap-allocated memory
    unique_ptr<int> p2(pi2);

// legal but p3 will call delete on a non-heap object ix
    unique_ptr<int> p3(&ix);

// correct use of unique_ptr
// p4 owns memory initialized by the call 'new int(2048)'
// it will be properly released once p4 goes out of scope
    unique_ptr<int> p4(new int(2048));

// legal but we now have two independent pointers to the same memory
// delete will be called twice one the same object
    unique_ptr<int> p5(p2.get());

// since C++14 we can use make_unique<>
    unique_ptr<int> p6 = make_unique<int>(42);
// for arrays - array of 5 ints
    unique_ptr<int[]> p7 = make_unique<int[]>(5);
// unique_ptr to array - manually
    unique_ptr<int[]> p8(new int[5]{1,2,3,4,5});
    for(int i=0; i<5; ++i){
        cout << p8[i] << ", " << std::flush;
    }
}
