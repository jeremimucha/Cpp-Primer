// ex 14.37
/*Write a class that tests whether two values are equal.
Use that object and the library algorithms to write a program to replace all
instances of a given value in a sequence.*/
#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;
using std::cout;
using std::endl;


class Equaltest
{
public:
    Equaltest(int val)
        : testval(val){ }
    bool operator()(int val)
        { return testval == val; }
private:
    int testval;
};


int main()
{
    vector<int> vi{0,4,2,1,0,0,34,0,12,0,11,9,0};
    std::replace_if(vi.begin(), vi.end(), Equaltest(0), 42);
    for(int i : vi)
        cout << i << ", ";
}
