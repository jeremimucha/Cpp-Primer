// ex9.39.cpp
/*Write a program to explore how  vector s grow in the library you use.*/
#include <iostream>
#include <vector>


template<typename Iter>
void print_container(Iter begin, Iter end);

void vinfo(std::vector<int>& vi);


int main()
{
    using std::cout; using std::endl;
    std::vector<int> vi;
    cout << "vi after default construction:\n";
    vinfo(vi);
    vi.insert(vi.end(),{1,2,3,4,5,6});
    cout << "\nvi afer  vi.insert(vi.end(),{1,2,3,4,5,6}):\n";
    vinfo(vi);
    vi.reserve(11);
    cout << "\nvi after vi.reserve(11):\n";
    vinfo(vi);
    vi.insert(vi.end(),{0,9,8,7,6,5,4,3,2,1});
    cout << "\nvi after vi.insert(vi.end(),{0,9,8,7,6,5,4,3,2,1}):\n";
    vinfo(vi);
    vi.shrink_to_fit();
    cout << "\nvi after vi.shrink_to_fit():\n";
    vinfo(vi);

    cout << "\n\nDone.\n";
    return 0;
}

template<typename Iter>
void print_container(Iter begin, Iter end)
{
    while(begin != end){
        std::cout << *begin;
        if( ++begin != end )
            std::cout << ", ";
    }
}

void vinfo(std::vector<int>& vi)
{
    std::cout << "size:     " << vi.size() << "\n";
    std::cout << "capacity: " << vi.capacity() << "\n";
}
