// test code for StrBlob class
#include <iostream>
#include <string>
#include "blob.h"
#include "blobptr.h"
#include "constblobptr.h"


int main()
{
    // StrBlob blob{"here's", "an", "initializer", "list", "StrBlob"};
    // {
    //     StrBlob blob2{"different", "blob"};
    //     StrBlob blob3(blob);
    //     std::cout << "blob2 back: " << blob2.back() << "\n";
    //     blob2 = blob;
    // }
    Blob<std::string> blob1{"one", "two", "three", "four", "five", "six"};
    Blob<std::string> blob2{"1", "2", "3", "4", "5", "6"};
    const Blob<std::string> blob3(blob2);
    blob2 = blob1;
    for(BlobPtr<std::string> it=blob1.begin(); it!=blob1.end();){
        std::cout << *it;
        if( ++it != blob1.end() )
            std::cout << ", ";
    }
    for(ConstBlobPtr<std::string> it=blob3.cbegin(); it!=blob3.cend();){
        std::cout << *it;
        if( ++it != blob3.cend() )
            std::cout << ", ";
    }
}
