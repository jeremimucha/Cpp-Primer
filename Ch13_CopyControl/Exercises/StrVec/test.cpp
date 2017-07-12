#include <iostream>
#include <algorithm>


int main()
{
    const char arr[] = "123456789";
    constexpr size_t sizearr = sizeof(arr) / sizeof(*arr);
    std::for_each(arr, arr+sizearr, [](char c){std::cout << c <<", ";});
}