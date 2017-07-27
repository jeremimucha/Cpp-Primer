/* Exercise 16.47: Write your own version of the flip function and test it by
calling functions that have lvalue and rvalue reference parameters. */
#include <iostream>
#include <utility>
#include <string>
using std::cout;
using std::endl;
using std::string;


template<typename F, typename T1, typename T2>
auto flip(F f, T1&& t1, T2&& t2) -> decltype(f(t2,t1))
{
    return f(std::forward<T2>(t2), std::forward<T1>(t1));
}


double f1(int i, double d);
string& f2(string& s, char ch);
string f3(const string& s, char ch);
string f4(string&& s1, const string& s2);


int main()
{
    string s{"foo"};
    const string cs{"foobar"};
    
    auto res1 = flip(f1, 11.1, 42);
    cout << "flip(f1, 11.1, 42) = " << res1 << endl;

    auto res2 = flip(f2, 'B', s);
    cout << "flip(f2, 'B', s) = " << res2 << endl;

    auto res3 = flip(f3, '!', cs);
    cout << "flip(f3, '!', cs) = " << res3 << endl;

    auto res4 = flip(f4, cs, "FOOBAR");
    cout << "flip(f4, cs, \"FOOBAR\") = " << res4 << endl;
}


double f1(int i, double d)
{
    cout << "f1(" << i << ", " << d << ")" << endl;
    return i + d;
}

string& f2(string& s, char ch)
{
    cout << "f2(" << s << ", " << ch << ")" << endl;
    s.push_back(ch);
    return s;
}

string f3(const string& s, char ch)
{
    cout << "f3(" << s << ", " << ch << ")" << endl;
    return s + ch;
}

string f4(string&& s1, const string& s2)
{
    cout << "f4(" << s1 << ", " << s2 << ")" << endl;
    s1.append(s2);
    return s1;
}
