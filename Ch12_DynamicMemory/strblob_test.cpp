// test code for StrBlob class
#include <iostream>
#include "strblob.h"


int main()
{
    StrBlob blob{"here's", "an", "initializer", "list", "StrBlob"};
    {
        StrBlob blob2{"different", "blob"};
        StrBlob blob3(blob);
        std::cout << "blob2 back: " << blob2.back() << "\n";
        blob2 = blob;
    }
    std::cout << "Almost done!\n";    
}
