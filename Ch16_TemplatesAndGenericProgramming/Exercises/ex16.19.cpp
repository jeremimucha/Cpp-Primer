/* Exercise 16.19: Write a function that takes a reference to a container
and prints the elements in that container. Use the container’s  size_type
and  size members to control the loop that prints the elements. */
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;


template<typename Cont>
void print_container(const Cont& container);


int main()
{
    vector<int> vi{1,2,3,4,5,6,7,8,9};
    cout << "vi: ";
    print_container(vi);
}


template<typename Cont>
void print_container(const Cont& container)
{
    for(typename Cont::size_type i=0; i<container.size();){
        std::cout << container[i];
        if(++i<container.size()) std::cout << ", ";
    }
}
