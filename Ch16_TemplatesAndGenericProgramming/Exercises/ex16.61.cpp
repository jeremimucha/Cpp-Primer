/* Exercise 16.61: Define your own version of  make_shared . */
#include <iostream>
#include <memory>
#include <utility>
using std::string;
using std::cout;
using std::endl;


template<typename T, typename... Args>
std::shared_ptr<T> makeshared(Args&&... args);


int main()
{
    std::shared_ptr<string> sps = makeshared<string>(5, 'S');
}


template<typename T, typename... Args>
std::shared_ptr<T> makeshared(Args&&... args)
{
    return std::shared_ptr<T>(new T(std::forward<Args>(args)...));
}
