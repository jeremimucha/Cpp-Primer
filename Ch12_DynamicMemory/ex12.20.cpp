// ex 12.20
/*Write a program that reads an input file a line at a time
into a  StrBlob and uses a  StrBlobPtr to print each element in that  StrBlob .*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <iterator>
#include <cstdlib>
#include <utility>
#include "strblob.h"
#include "strblobptr.h"
#include "conststrblobptr.h"
using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::string;



int main(int argc, char* argv[])
{
    if(argc != 2){
        std::cerr << "Usage: " << argv[0] << " inputfile\n";
        std::exit(EXIT_FAILURE);
    }
    ifstream ifs{argv[1]};
    if(!ifs.is_open()){
        std::cerr << "Failed to open the file " << argv[1] << "\n";
        std::exit(EXIT_FAILURE);
    }

    StrBlob blob;
    string line;
    while( getline(ifs, line) )
        blob.push_back(std::move(line));
    
    for(StrBlobPtr it=blob.begin(); it!=blob.end(); it.incr()){
        cout << it.deref() << "\n";
    }
    cout << "\nUsing ConstStrBlobPtr:\n";
    for(ConstStrBlobPtr it=blob.cbegin(); it!=blob.cend(); it.incr()){
        cout << it.deref() << "\n";
    }
}
