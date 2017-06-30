// exs9.2.4.cpp -- Chapter 9 exercise section 9.2.4
/*9.11: Show an example of each of the six ways to create and
initialize a  vector . Explain what values each  vector contains.
9.13: How would you initialize a  vector<double> from a
list<int> ? From a  vector<int> ? Write code to check your answers.*/
#include <iostream>
#include <vector>
#include <list>
#include <utility>


template<typename Iter>
void print_container(Iter begin, Iter end);


int main()
{
    using namespace std;
    vector<char> v1;   // 1
    vector<char> v2(9);
    vector<char> v3(11, '+');
    vector<char> v4(v3);
    vector<char> v5(v3.begin(), v3.end());
    vector<char> v6{'f', 'o', 'o', 'b', 'a', 'r'};

    for(const auto vec : {&v1, &v2, &v3, &v4, &v5, &v6}){
        print_container(vec->begin(), vec->end());
        std::cout << "----------------------------------------\n";
    }

    vector<int> vi(42, 11);
    list<int> li(27, 42);

    vector<double> vd1(vi.begin(), vi.end());
    vector<double> vd2(li.begin(), li.end());

    std::cout << "\nvector<int> vi:\n";
    print_container(vi.begin(), vi.end());
    std::cout << "\nlist<int> li:\n";
    print_container(li.begin(), li.end());
    std::cout << "\nvector<double> vd1(vi.begin(), vi.end()):\n";
    print_container(vd1.begin(), vd1.end());
    std::cout << "\nvector<double> vd2(li.begin(), li.end()):\n";
    print_container(vd2.begin(), vd2.end());

    std::cout << "\nDone.\n";
    return 0;
}


template<typename Iter>
void print_container(Iter begin, Iter end)
{
    while(begin != end){
        std::cout << *begin++;
        if( begin != end )
            std::cout << ", ";
    }
    std::cout << "\n";
}
