#ifndef HASPTR_H_
#define HASPTR_H_

#include <iostream>


class HasPtr
{
public:
// constructor allocates a new string and a new counter, which it sets to 1
    HasPtr(const std::string& s=std::string())
        : ps(new std::string(s)), i(0), use(new std::size_t(1))
        { info("HasPtr(const string&)"); }
// copy constructor copies all three data members and increments the counter
    HasPtr(const HasPtr& p)
        : ps(p.ps), i(p.i), use(p.use)
        { ++*use; info("HasPtr(const HasPtr&)"); }
    ~HasPtr()
        {
            info("~HasPtr()"); 
            if( --*use == 0 ){  // if reference goes down to zero
                delete ps;      // delete the string
                delete use;     // and the counter
            }
        }
    HasPtr& operator=(const HasPtr& p);
friend std::ostream& operator<<(std::ostream& os, const HasPtr& hp);
private:
    std::string* ps;
    int i;
    std::size_t* use;     // member to keep track of how many objects share *ps

    void info(const char* str)
        {
            std::cout << str << ", ps: " << reinterpret_cast<void*>(ps)
                      << ", *ps: " << *ps << ", use: " << reinterpret_cast<void*>(use)
                      << ", *use: " << *use << ", i: " << i << "\n";
        }
};


inline HasPtr& HasPtr::operator=(const HasPtr& rhs)
{
    // if( this == &rhs )
    //     return *this;
    
    // if(--*use == 0){
    //     delete ps;
    //     delete use;
    // }
    // ps = rhs.ps;
    // use = ++*rhs.use;
    // i = rhs.i;

// or
    ++*rhs.use;           // increment the use count of the right-hand operand
    if(--*use == 0){    // then decrement this object's counter
        delete ps;      // if no other users
        delete use;     // free this object's allocated members
    }
    ps = rhs.ps;            // copy data from rhs into this object
    i = rhs.i;
    use = rhs.use;

    info("HasPtr::operator=(const HasPtr&)");
    return *this;
}


inline std::ostream& operator<<(std::ostream& os, const HasPtr& hp)
{
    return os << *hp.ps << ", 0x" << reinterpret_cast<void*>(hp.ps)
              << ", i = " << hp.i;
}


#endif /*HASPTR_H_*/
