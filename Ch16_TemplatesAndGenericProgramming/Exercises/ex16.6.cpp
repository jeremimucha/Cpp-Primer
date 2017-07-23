/* Exercise 16.6: How do you think the library  begin and  end functions that
take an array argument work? Define your own versions of these functions.
*/
#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;


template<typename T, unsigned N>
constexpr T* mybegin(T(&arr)[N]) noexcept;

template<typename T, unsigned N>
constexpr T* myend(T(&arr)[N]) noexcept;


int main()
{
    int arrint[]{1,2,3,4,5,6};
    double arrdouble[]{1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    cout << "*mybegin(arrint): " << *mybegin(arrint) << endl;
    cout << "for_each(mybegin(arrint), myend(arrint), cout << i): ";
    std::for_each(mybegin(arrint), myend(arrint),
                  [](int i){std::cout << i << ", ";});
    cout << "\nfor_each(mybegin(arrdouble), myend(arrdouble), cout << d): ";
    std::for_each(mybegin(arrdouble), myend(arrdouble),
                  [](double d){std::cout << d << ", "; });
}


template<typename T, unsigned N>
constexpr T* mybegin(T(&arr)[N]) noexcept
{
    return &arr[0];
}

template<typename T, unsigned N>
constexpr T* myend(T(&arr)[N]) noexcept
{
    return &arr[N];
}
