/* Exercise 16.48: Write your own versions of the  debug_rep functions. 
Exercise 16.65: In § 16.3 (p. 698) we defined overloaded two versions of
debug_rep one had a  const char* and the other a  char* parameter. Rewrite
these functions as specializations.*/
#include <iostream>
#include <sstream>
#include <string>
using std::cout;
using std::endl;


template<typename T> std::string debug_rep(const T& t);
template<typename T> std::string debug_rep(T* p);
std::string debug_rep(const std::string& s);
std::string debug_rep(char* p);
std::string debug_rep(const char* p);

// specializations
// template<> std::string debug_rep<const char*>(const char* const& p)


int main()
{
    std::string s("foo");
    const char* cstr{"cfoo"};
    std::string* null = nullptr;
    cout << "debug_rep(s): " << debug_rep(s) << endl;
    cout << "debug_rep(&s): " << debug_rep(&s) << endl;
    cout << "debug_rep(nullptr): " << debug_rep(null) << endl;
    cout << "debug_rep(cstr): " << debug_rep(cstr) << endl;
}


template<typename T> std::string debug_rep(const T& t)
{
    std::ostringstream oss;
    oss << t;
    return oss.str();
}

template<typename T> std::string debug_rep(T* p)
{
    std::ostringstream oss;
    oss << "pointer: " << p;
    if(p)
        oss << " " << debug_rep(*p);
    else
        oss << " nullptr";
    return oss.str();
}

std::string debug_rep(const std::string& s)
{
    return '"' + s + '"';
}

std::string debug_rep(char* p)
{
    return debug_rep(std::string(p));
}

std::string debug_rep(const char* p)
{
    return debug_rep(std::string(p));
}
