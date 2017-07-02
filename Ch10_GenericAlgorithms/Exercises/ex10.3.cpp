// ex10.3.cpp
/*Use  accumulate to sum the elements in a  vector<int>*/
#include <iostream>
#include <vector>
#include <numeric>  // accumulate
using std::vector;
using std::cout;
using std::endl;


int main()
{
    vector<int> vi{1,2,3,4,5,6,7,8,9,10,11};
    int total = std::accumulate(vi.cbegin(), vi.cend(), 0);
    cout << "vi: ";
    for(auto i : vi) cout << i << " ";
    cout << "\nsum of elements: " << total;

}
