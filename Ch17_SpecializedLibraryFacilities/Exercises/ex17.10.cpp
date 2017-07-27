/* Exercise 17.10: Using the sequence 1, 2, 3, 5, 8, 13, 21, initialize a
bitset that has a  1 bit in each position corresponding to a number in this
sequence. Default initialize another  bitset and write a small program to
turn on each of the appropriate bits. */
#include <iostream>
#include <bitset>
using std::cout;
using std::endl;
using std::bitset;


// 0010 0000 0010 0001 0010 1110
//        20        21        2E

int main()
{
    bitset<32> b1(0x20212E);
    bitset<32> b2;
    int bits[]{1,2,3,5,8,13,21};
    for( int i : bits){
        b2.set(i);
    }
    cout << "b1: " << b1 << endl;
    cout << "b2: " << b2 << endl;
}
