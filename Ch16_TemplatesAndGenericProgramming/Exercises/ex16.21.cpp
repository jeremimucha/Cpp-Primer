/* Exercise 16.21: Write your own version of  DebugDelete . */
#include <iostream>
#include <string>
#include <memory>
using std::cout;
using std::endl;


class DebugDelete
{
public:
    DebugDelete(std::ostream& s=std::cerr)
        : os(s) { }
    template<typename T>
    void operator()(T* p) const
        { os << "deleting ptr "
             << reinterpret_cast<const void*>(p) << std::endl;
            delete p; }
private:
    std::ostream& os;
};



int main()
{
    int* pi = new int(42);
    DebugDelete dd;
    dd(pi);
    std::shared_ptr<std::string> sps(new std::string("foobar"),
                                     DebugDelete());
    std::unique_ptr<std::string,DebugDelete> ups(new std::string("foo"),DebugDelete());
}
