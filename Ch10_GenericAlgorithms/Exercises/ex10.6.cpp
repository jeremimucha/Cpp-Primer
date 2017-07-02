// ex10.6.cpp
/*Using  fill_n , write a program to set a sequence of  int
values to 0.*/
#include <iostream>
#include <vector>
#include <algorithm>


int main()
{
    std::vector<int> vi{1,2,3,4,5,6,7,8,9,10};
    std::cout << "vi: ";
    for(auto i : vi) std::cout << i << " ";
    std::cout << std::endl;
    std::fill_n(vi.begin(), vi.size(), 0);
    std::cout << "vi after fill_n: ";
    for(auto i : vi) std::cout << i << " ";
    std::cout << "\n\nDone.\n";
}
