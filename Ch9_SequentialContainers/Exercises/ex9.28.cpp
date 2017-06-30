// ex9.28.cpp
/*Write a function that takes a  forward_list<string> and two
additional  string arguments. The function should find the first  string and
insert the second immediately following the first. If the first  string is not
found, then insert the second  string at the end of the list.*/
#include <iostream>
#include <forward_list>
#include <string>
using std::forward_list;
using std::string;

forward_list<string>::const_iterator
insert_after(forward_list<string>& fls, const string& seek, const string& toinsert);

template<typename Iter>
void print_container(Iter begin, Iter end);

int main()
{
    forward_list<string> strings{"one", "two", "three", "five", "six", "seven"};
    forward_list<string> fls_empty;
    std::cout << "Before inserting: ";
    print_container(strings.cbegin(), strings.cend());
    insert_after(strings, "three", "FOUR");
    std::cout << "\nAfter inserting 'FOUR' following 'three':\n";
    print_container(strings.cbegin(), strings.cend());
    std::cout << "\nInserting into an empty flist:\n";
    insert_after(fls_empty, "three", "FOUR");
    std::cout << "\nEmpty flist after inserting 'FOUR' following 'three':\n";
    print_container(fls_empty.cbegin(), fls_empty.cend());

    std::cout << "\n\nDone.\n";
    return 0;
}


forward_list<string>::const_iterator
insert_after(forward_list<string>& fls, const string& seek, const string& toinsert)
{
    auto curr = fls.cbegin();
    auto prev = fls.cbefore_begin();
    while( curr != fls.cend() && *curr != seek ){
        ++curr;
        ++prev;
    }
    if( curr != fls.cend() )
        return fls.insert_after(curr, toinsert);
    else
        return fls.insert_after(prev, toinsert);
}

template<typename Iter>
void print_container(Iter begin, Iter end)
{
    while( begin != end ){
        std::cout << *begin;
        if( ++begin != end )
            std::cout << ", ";
    }
}
