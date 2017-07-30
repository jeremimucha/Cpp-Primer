#include <iostream>


// example of an implementation of the std::move template
template<typename T>
typename remove_reference<T>::type&& move(T&& t)
{
    return static_cast<typename remove_reference<T>::type&&>(t);
}

int main()
{

}
