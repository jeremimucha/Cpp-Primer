// ex13.18
#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include <iostream>
#include <string>


class Employee
{
public:
    Employee()
        : Employee("noname")
        { std::cout << "Employee()" << std::endl; }
    Employee(const std::string& name)
        : id(ID_++), fullname(name)
        { std::cout << "Employee(const string&)" << std::endl; }
    Employee(const Employee& e)
        : id(ID_++), fullname(e.fullname)
        { std::cout << "Employee(const Employee&)" << std::endl; }
    Employee& operator=(const Employee& e)
        {
            std::cout << "Employee::operator=(const Employee& e)" << std::endl;
            if(this == &e)
                return *this;
            fullname = e.fullname;
            return *this;
        }
friend std::ostream& operator<<(std::ostream& os, const Employee& e);
private:
    size_t id;
    std::string fullname;
    static size_t ID_;
};

inline std::ostream& operator<<(std::ostream& os, const Employee& e)
{
    return os << e.id << ": " << e.fullname;
}


#endif /*EMPLOYEE_H_*/
