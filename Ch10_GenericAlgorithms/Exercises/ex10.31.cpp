// ex10.31.cpp
/*Update the program from the previous exercise so that it
prints only the unique elements. Your program should use  unqiue_copy (§
10.4.1, p. 403)*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
using std::vector;
using std::istream_iterator;
using std::ostream_iterator;
using std::cin; using std::cout;


int main()
{
    cout << "Enter some integers: ";
    vector<int> numbers;
    std::copy(istream_iterator<int>(cin), istream_iterator<int>(),
              std::back_inserter(numbers));
    std::sort(numbers.begin(), numbers.end());
    cout << "\nHere are your sorted ints: ";
    std::unique_copy(numbers.cbegin(), numbers.cend(), ostream_iterator<int>(cout, ", "));
}
