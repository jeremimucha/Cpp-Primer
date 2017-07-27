

#include <iostream>
#include <sstream>
#include <string>

template<typename T>
std::ostream& print(std::ostream& os, const T& t);
template<typename T, typename... Args>
std::ostream& print(std::ostream& os, const T&, const Args&... rest);

template<typename T> std::string debug_rep(const T& t);
template<typename T> std::string debug_rep(T* p);
std::string debug_rep(const std::string& s);
std::string debug_rep(char* p);
std::string debug_rep(const char* p);

template<typename... Args>
std::ostream& errorMsg(std::ostream& os, const Args&... rest);


int main()
{
    errorMsg(std::cout, "one", 2, '3', 4.4, std::string("five"));
}


template<typename T>
std::ostream& print(std::ostream& os, const T& t)
{
    return os << t;     // no separator after the last element in the pack
}

template<typename T, typename... Args>
std::ostream& print(std::ostream& os, const T& t, const Args&... rest)
{
    os << t << ", ";            // print the first argument
    return print(os, rest...);  // recursive call, print the other arguments
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


template<typename... Args>
std::ostream& errorMsg(std::ostream& os, const Args&... rest)
{   
    // debug_rep(rest)... unpacking pattern is applied to the 
    // 'rest' parameter pack. This means that in the process
    // of unpacking debug_rep() will be applied to all of the
    // parameters in the 'rest' param pack.
    return print(os, debug_rep(rest)...);
}
