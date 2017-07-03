// ex10.30.cpp
/*Use stream iterators,  sort , and  copy to read a sequence
of integers from the standard input, sort them, and then write them back
to the standard output.*/
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
    std::copy(numbers.cbegin(), numbers.cend(), ostream_iterator<int>(cout, ", "));
}
