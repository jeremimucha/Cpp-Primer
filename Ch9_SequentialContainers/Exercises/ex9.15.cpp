// ex9.15.cpp -- Chapter 9
/*9.15: Write a program to determine whether two  vector<int>s are equal.
9.16: Repeat the previous program, but compare elements in a
list<int> to a  vector<int> .*/
#include <iostream>
#include <vector>
#include <list>


template<typename Iter>
void print_container(Iter begin, Iter end);

template<typename T>
bool operator<(const std::vector<T>& a, const std::list<T>& b);

template<typename IterA, typename IterB>
bool compare_ranges(IterA abegin, IterA aend, IterB bbegin, IterB bend);

int main()
{
    using std::cout; using std::endl;
    cout.setf(std::ios_base::boolalpha);

    std::vector<int> v1{1,2,3,4,5,6};
    std::vector<int> v2{1,2,3,4};
    std::vector<int> v3(v1);
    std::vector<int> v4{1,2,3,5};

    const std::vector<int>* arv[]{&v1, &v2, &v3, &v4};
    int i{1};
    for(auto v=begin(arv); v!=end(arv); ++v, ++i){
        std::cout << "v" << i << ": ";
        print_container((*v)->cbegin(), (*v)->cend());
        std::cout << "\n";
    }

    std::cout << "v1 < v2: "  << (v1 < v2) << "\n";
    std::cout << "v1 == v3: "  << (v1 == v3) << "\n";
    std::cout << "v1 < v4: " << (v1 < v4) << "\n";

    std::list<int> l1(v1.cbegin(), v1.cend());
    i=1;
    for(auto v=begin(arv); v!=end(arv); ++v, ++i){
        std::cout << "v" << i <<" < l1: ";
        std::cout << (**v < l1) << "\n";
    }

    std::cout << "\nUsing iterators:\n";
    i=1;
    for(auto v=begin(arv); v!=end(arv); ++v, ++i){
        std::cout << "v" << i << " < li: ";
        std::cout << compare_ranges((*v)->cbegin(), (*v)->cend(),
                     l1.cbegin(), l1.cend()) << "\n";
    }
}

template<typename Iter>
void print_container(Iter begin, Iter end)
{
    while(begin != end){
        std::cout << *begin++;
        if( begin != end )
            std::cout << ", ";
    }
}

template<typename T>
bool operator<(const std::vector<T>& a, const std::list<T>& b)
{
    typename std::vector<T>::const_iterator aiter = a.cbegin();
    typename std::list<T>::const_iterator biter = b.cbegin();
    while( aiter != a.cend() && biter != b.cend() ){
        if( *aiter < *biter )
            return true;
        else if( *aiter > *biter )
            return false;
        ++aiter; ++biter;
    }
    return (aiter == a.cend() && biter != b.cend() );
}

template<typename IterA, typename IterB>
bool compare_ranges(IterA abegin, IterA aend, IterB bbegin, IterB bend)
{
    while( abegin != aend && bbegin != bend ){
        if( *abegin < *bbegin )
            return true;
        else if( *bbegin > *bbegin )
            return false;
        ++abegin; ++bbegin;
    }
    return (abegin == aend && bbegin != bend);
}
