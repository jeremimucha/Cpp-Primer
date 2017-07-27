/* Exercise 16.51: Determine what  sizeof...(Args) and  sizeof...(rest)
return for each call to  foo in this section.
Exercise 16.52: Write a program to check your answer to the previous
question. */
#include <iostream>



template<typename T, typename... Args>
void foo(const T& t, const Args&... rest);


int main()
{
    foo(1, "two", 3.3, "four", 'f');
}


template<typename T, typename... Args>
void foo(const T& t, const Args&... rest)
{
    std::cout << "sizeof...(Args): " << sizeof...(Args);
    std::cout << ", sizeof...(rest): " << sizeof...(rest) << std::endl;
}
