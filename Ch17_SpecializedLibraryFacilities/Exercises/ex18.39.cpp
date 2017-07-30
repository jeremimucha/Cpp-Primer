/* Exercise 17.39: Write your own version of the  seek program presented in
this section. */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using std::cout;
using std::endl;
using std::fstream;
using std::string;




int main(int argc, char* argv[])
{
    if( argc != 2 ){
        std::cerr << "Usage: " << argv[0] << " inputfile\n";
        exit(EXIT_FAILURE);
    }
    
    // open for input and output and preposition file pointers to end-of-file
    fstream inOut(argv[1], fstream::ate | fstream::in | fstream::out);
    if(!inOut.is_open()){
        std::cerr << "Unable to open the file " << argv[1] << endl;
        exit(EXIT_FAILURE);
    }
    // inOut is opened in ate mode, so it starts out positioned at the end
    fstream::pos_type end_mark = inOut.tellg(); // remember original EOF position
    inOut.seekg(0, fstream::beg);               // reposition to the start of the file
    size_t count = 0;                           // accumulator for teh byte count
    string line;
    // while we haven't hit an error and are still reading the original data
    while(inOut && inOut.tellg() != end_mark
          && getline(inOut, line) ){        // and can get another line of input
        count += line.size() + 1;           // add 1 to account for newline
        fstream::pos_type mark = inOut.tellg(); // remember the read position
        inOut.seekp(0, fstream::end);           // set the write marker to the end
        inOut << count;
        // print a separator if this is not the last line
        if( mark != end_mark ) inOut << " ";
        inOut.seekg(mark);                      // restore teh read position
    }
    inOut.seekp(0, fstream::end);               // seek to the end
    inOut << "\n";                              // write newline to the end of file
    return 0;
}
