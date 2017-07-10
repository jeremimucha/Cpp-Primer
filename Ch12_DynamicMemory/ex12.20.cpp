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
<<<<<<< HEAD
using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::string;

=======
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;
>>>>>>> 542e774ef888abf418964a6997031e98a15bf5f6


int main(int argc, char* argv[])
{
    if(argc != 2){
<<<<<<< HEAD
        std::cerr << "Usage: " << argv[0] << " inputfile\n";
        std::exit(EXIT_FAILURE);
=======
        std::cerr << "Usage: " << argv[0] << " inputfile.\n";
        exit(EXIT_FAILURE);
>>>>>>> 542e774ef888abf418964a6997031e98a15bf5f6
    }
    ifstream ifs{argv[1]};
    if(!ifs.is_open()){
        std::cerr << "Failed to open the file " << argv[1] << "\n";
<<<<<<< HEAD
        std::exit(EXIT_FAILURE);
=======
        exit(EXIT_FAILURE);
>>>>>>> 542e774ef888abf418964a6997031e98a15bf5f6
    }

    StrBlob blob;
    string line;
<<<<<<< HEAD
    while( getline(ifs, line) )
        blob.push_back(std::move(line));
    
    for(StrBlobPtr it=blob.begin(); it!=blob.end(); it.incr()){
        cout << it.deref() << "\n";
    }
    cout << "\nUsing ConstStrBlobPtr:\n";
    for(ConstStrBlobPtr it=blob.cbegin(); it!=blob.cend(); it.incr()){
        cout << it.deref() << "\n";
=======
    while( getline(ifs, line) ){
        blob.push_back(std::move(line));
    }

    for(StrBlobPtr it=blob.begin(); it!=blob.end(); it.incr()){
        std::cout << it.deref() << ", ";
    }
    const StrBlob cblob{blob};
    cout << "\nUsing a const:\n";
    for(ConstStrBlobPtr it=cblob.cbegin(); it!=cblob.cend(); it.incr()){
        std::cout << it.deref() << "||";
>>>>>>> 542e774ef888abf418964a6997031e98a15bf5f6
    }
}
