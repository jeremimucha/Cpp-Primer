// ex 12.24
/*Write a program that reads a string from the standard
input into a dynamically allocated character array. Describe how your
program handles varying size inputs. Test your program by giving it a
string of data that is longer than the array size you’ve allocated.*/
#include <iostream>
#include <cstring>
#include <memory>
using std::cout;
using std::cin;
using std::endl;
using std::strcpy;
using std::strcat;
using std::unique_ptr;


char* get_line(std::istream& is);

int main()
{
    cout << "Enter some text: ";
    // unique_ptr<char[]> line;
    char* line;
    while( (line = get_line(cin)) && line[0] != '\0' ){
        cout << "Echo: " << line << "\n";
        delete[] line;
    }
}

char* get_line(std::istream& is)
{
    static const size_t sizebuff = 20;
    static char buffer[sizebuff];
    size_t size_line = 0;
    char* line = nullptr;

    while( is.get(buffer, sizebuff) ){
        int next = is.peek();
        size_line += (next != '\n' ? sizebuff : is.gcount() + 1);
        char* t = new char[size_line];
        if(line)
            strcpy(t, line);
        else
            t[0] = '\0';
        delete[] line;
        line = t;
        strcat(line, buffer);
        if( next == '\n' ){
            is.get();
            break;
        }
    }

    return line;
}
