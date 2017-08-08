#ifndef DEBUGDELETE_H_
#define DEBUGDELETE_H_

#include <iostream>
#include <memory>


class DebugDelete
{
public:
    DebugDelete(std::ostream& s=std::cerr)
        : os(s) { }
    template<typename T>
    void operator()(T* p) const
        {
            os << "deleting ptr " << reinterpret_cast<const void*>(p)
               << std::endl;
            delete p;
        }
private:
    std::ostream& os;
};


#endif /* DEBUGDELETE_H_ */
