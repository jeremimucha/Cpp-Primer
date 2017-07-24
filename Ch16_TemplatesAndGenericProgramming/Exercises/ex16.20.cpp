/* Exercise 16.20: Write a function that takes a reference
 * to a container and prints the elements. Use begin and end.
 */
#include <iostream>
#include <vector>


template<typename Cont>
void print_container(const Cont& c);


int main()
{
    std::vector<int> vi{1,2,3,4,5,6,7,8,9};
    std::cout << "vi: ";
    print_container(vi);
}

template<typename Cont>
void print_container(const Cont& c)
{
    for(typename Cont::const_iterator it = c.cbegin();
        it != c.cend();
       ){
           std::cout<< *it;
           if(++it != c.cend()) std::cout << ", ";
       }
}
