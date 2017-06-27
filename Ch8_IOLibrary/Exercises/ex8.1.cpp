// ex8.1.cpp -- Chapter 8
/*Write a function that takes and returns an  istream& . The
function should read the stream until it hits end-of-file. The function should
print what it reads to the standard output. Reset the stream so that it is
valid before returning the stream.*/
#include <iostream>


std::istream& echo(std::istream& is);


int main()
{

}


std::istream& echo(std::istream& is)
{
    char ch;
    while(is.get(ch)){
        std::cout << ch;
    }
    is.clear();
    return is;
}