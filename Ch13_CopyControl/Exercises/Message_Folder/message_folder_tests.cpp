#include <iostream>
#include "message.h"
#include "folder.h"


int main()
{
    Folder f1;
    Folder f2;
    Message m1("message 1");
    Message m2("message 2");
    m1.save(f1);
    m2.save(f2);
    std::cout << "f1: " << f1 << "\n";
    std::cout << "f2: " << f2 << "\n";
    Folder f3(f1);
    Message m3(m1);
    Message m4(m2);
    std::cout << "f3: " << f3 << "\n";
    std::cout << "f1: " << f1 << "\n";
    Folder f4 = std::move(f1);
    std::cout << "f4: " << f4 << "\n";
    // std::cout << "f1: " << f1 << "\n";
}
