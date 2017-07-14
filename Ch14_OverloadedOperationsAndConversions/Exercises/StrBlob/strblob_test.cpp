// test code for StrBlob class
#include <iostream>
#include "strblob.h"
#include "strblobptr.h"
#include "conststrblobptr.h"
#include "strblobptrptr.h"
using std::cout;
using std::endl;

int main()
{
    // StrBlob blob{"here's", "an", "initializer", "list", "StrBlob"};
    // {
    //     StrBlob blob2{"different", "blob"};
    //     StrBlob blob3(blob);
    //     std::cout << "blob2 back: " << blob2.back() << "\n";
    //     blob2 = blob;
    // }
    StrBlob sb1({"foo"});
    StrBlob sb2({"foo"});
    StrBlob sb3({"bar"});
    cout.setf(std::ios_base::boolalpha);
    cout << "sb1 == sb2: " << (sb1 == sb2) << endl;
    cout << "sb1 == sb3: " << (sb1 == sb3) << endl;
    cout << "sb1 != sb3: " << (sb1 != sb3) << endl;

    cout << "\n";
    StrBlob sb4({"one", "two", "three", "four", "five"});
    const StrBlob sb5({"1", "2", "3", "4", "5"});
    cout << "sb4[0], sb4[1]: " << sb4[0] <<", " << sb4[1] << endl;
    cout << "sb5[0], sb5[1]: " << sb5[0] <<", " << sb5[1] << endl;
    StrBlobPtr psb = sb4.begin();
    cout << "psb[0]: " << psb[0] << endl;
    cout << "(++psb)[0]: " << (++psb)[0] << endl;
    cout << "*psb: " << *psb << endl;
    cout << "psb->size(): " << psb->size() << endl;
    ConstStrBlobPtr cpsb = sb5.cbegin();
    cout << "cpsb[0]: " << cpsb[0] << endl;
    cout << "(++cpsb)[0]: " << (++cpsb)[0] << endl;
    cout << "*cpsb: " << *cpsb << endl;
    // takes the string returned by *cpsb, takes it's address (makes it into a pointer)
    // and calls size() on it
    cout << "cpsb->size(): " << cpsb->size() << endl;

    cout << "\nStrBlobPtrPtr tests:";
    cout << "\n-----------------------------------\n";
    StrBlobPtrPtr ppsb4(psb);
    cout << "(*ppsb4)[0]: " << (*ppsb4)[0] << endl;
    cout << "**ppsb4: " << **ppsb4 << endl;
    cout << "ppsb4->deref(): " << ppsb4->deref() << endl;
}
