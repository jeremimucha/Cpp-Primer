/* Exercise 17.37: Use the unformatted version of  getline to read a file a
line at a time. Test your program by giving it a file that contains empty
lines as well as lines that are longer than the character array that you pass
to  getline . 
Exercise 17.38: Extend your program from the previous exercise to print
each word you read onto its own line.*/
#include <iostream>
#include <fstream>
using std::cout;
using std::cerr;
using std::endl;
using std::cin;


const unsigned sizebuf = 3;
char buf[sizebuf];


int main(int argc, char* argv[])
{
    if(argc != 2){
        cerr << "Usage: " << argv[0] << " input_file\n";
        exit(EXIT_FAILURE);
    }
    std::ifstream ifs{argv[1]};
    if(!ifs.is_open()){
        cerr << "Failed to open the file " << argv[1] << endl;
        exit(EXIT_FAILURE);
    }

    while(!ifs.eof()){
        if( ifs.getline(buf, sizebuf, ' ') )
            cout << buf << endl;
        else{
            cout << buf;
            if(ifs.fail() && !ifs.eof())
                ifs.clear();
        }
    }
}
