// person.h -- Chapter 7 exercises - implementing a class
#ifndef PERSON_H_
#define PERSON_H_

#include <string>


class Person
{
private:
    std::string name;
    std::string address;
public:
    Person() = default;
    Person(const std::string& n, const std::string& addr)
        : name(n), address(addr) { }
    const std::string& Name() const { return name; }
    const std::string& Address() const { return address; }
};



#endif /*PERSON_H_*/
