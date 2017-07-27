/* Exercise 16.49: Explain what happens in each of the following calls:
Code:
template <typename T> void f(T);
template <typename T> void f(const T*);
template <typename T> void g(T);
template <typename T> void g(T*);
int i = 42, *p = &i;
const int ci = 0, *p2 = &ci;
g(42); g(p); g(ci); g(p2);
f(42); f(p); f(ci); f(p2);
Exercise 16.50: Define the functions from the previous exercise so that
they print an identifying message. Run the code from that exercise. If the
calls behave differently from what you expected, make sure you
understand why. */
#include <iostream>
using std::cout;
using std::endl;


template<typename T> void f(T);
template<typename T> void f(const T*);
template<typename T> void g(T);
template<typename T> void g(T*);


int main()
{
    int i = 42, *p = &i;
    const int ci = 0, *p2 = &ci;

    g(42);  // -> g(T), T = int
    g(p);   // -> g(T*), T = int*
    g(ci);  // -> g(T), T = const int
    g(p2);  // -> g(T*), T = const int*
    f(42);  // -> f(T), T = int
    f(p);   // -> f(T), T = int*
    f(ci);  // -> f(T), T = const int
    f(p2);  // -> f(const T*), T = int
}


template<typename T> void f(T)
{
    cout << "f(T)" << endl;
}
template<typename T> void f(const T*)
{
    cout << "f(const T*)" << endl;
}
template<typename T> void g(T)
{
    cout << "g(T)" << endl;
}
template<typename T> void g(T*)
{
    cout << "g(T*)" << endl;
}
