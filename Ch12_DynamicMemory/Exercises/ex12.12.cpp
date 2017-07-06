// ex12.12
/*Using the declarations of  p and  sp explain each of the
following calls to  process . If the call is legal, explain what it does. If the
call is illegal, explain why:*/
#include <iostream>
#include <memory>
#include <iomanip>
using std::cout;
using std::endl;
using std::showbase;
using std::shared_ptr;
using std::make_shared;


void process(shared_ptr<int> p);


int main()
{
    cout << showbase;

    int* p = new int(11);
    shared_ptr<int> sp = make_shared<int>(42);
    
// correct use of shared_ptr
    process(sp);           

// illegal - can't initialize shared_ptr implicitly
    // process(new int());             
    
// illegal - can't initialize shared_ptr implicitly
    // process(p);                     
   
// legal, but faulty use of shared_ptr
// will destroy the object pointed to by p at the end of function's scope
    process(shared_ptr<int>(p));    
}


void process(shared_ptr<int> p)
{
    cout << "shared_ptr<int>: " << reinterpret_cast<void*>(p.get())
         << ", value: " << *p << "\n";
}
