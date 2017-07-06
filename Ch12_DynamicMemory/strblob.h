// strblob.h
// Chapter 12 Dynamic Memory - example of a class using shared_ptr
#ifndef STRBLOB_H_
#define STRBLOB_H_

#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <stdexcept>

class StrBlobPtr;

class StrBlob
{
public:
    friend class StrBlobPtr;
    typedef std::vector<std::string>::size_type size_type;

    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    ~StrBlob() { std::cout << "--> ~StrBlob(): data = 0x"
                 << reinterpret_cast<void*>(data.get()) << ", use_count = "
                 << data.use_count() << "\n"; }
    
    bool empty() const
        { return data->empty(); }
    
    // add and remove elements
    void push_back(const std::string& t)
        {data->push_back(t);}
    void pop_back();
    
    // element access
    std::string& front();
    const std::string& front() const;
    std::string& back();
    const std::string& back() const;
    
    // return StrBlobPtr to the first and one past the last elements
    StrBlobPtr begin();
    StrBlobPtr end();

private:
    std::shared_ptr<std::vector<std::string>> data;
    // throws msg if data[i] isn't valid
    void check(size_type i, const std::string& msg) const;
};

inline StrBlob::StrBlob()
    : data(std::make_shared<std::vector<std::string>>())
    { std::cout << "--> StrBlob(): data = 0x"
        << reinterpret_cast<void*>(data.get()) 
        << " use_count = " <<data.use_count() << "\n"; }

inline StrBlob::StrBlob(std::initializer_list<std::string> il)
    : data(std::make_shared<std::vector<std::string>>(il))
    { std::cout << "--> StrBlob(initializer_list<string>): data = 0x"
                << reinterpret_cast<void*>(data.get()) 
                << " use_count = " << data.use_count() << "\n"; }

inline void StrBlob::check(size_type i, const std::string& msg) const
{
    if(i >= data->size())
        throw std::out_of_range(msg);
}

inline std::string& StrBlob::front()
{
    // if the vector is empty, check will throw
    check(0, "front() on empty StrBlob");
    return data->front();
}

inline const std::string& StrBlob::front() const
{
    check(0, "front() on empty StrBlob");
    return data->front();
}

inline std::string& StrBlob::back()
{
    check(0, "back() on empty StrBlob");
    return data->back();
}

inline const std::string& StrBlob::back() const
{
    check(0, "back() on empty StrBLob");
    return data->back();
}

inline void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

#endif /*STRBLOB_H_*/
