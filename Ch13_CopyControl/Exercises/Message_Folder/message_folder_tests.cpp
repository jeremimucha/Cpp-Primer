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
    std::cout << "\nf2: " << f2 << "\n";
}
