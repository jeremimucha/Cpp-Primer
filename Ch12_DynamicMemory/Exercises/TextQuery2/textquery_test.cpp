#include <iostream>
#include <fstream>
#include <string>
#include "textquery.h"
using std::cout; using std::endl;
using std::cin;
using std::string;
using std::ifstream;


int main(int argc, char* argv[])
{
    if(argc != 2){
        std::cerr << "Usage: " << __FILE__ << " input_file\n";
        exit(EXIT_FAILURE);
    }
    ifstream ifs{argv[1]};
    if(!ifs.is_open()){
        std::cerr << "Failed to open the file " << argv[1] << "\n";
        exit(EXIT_FAILURE);
    }

    TextQuery tq(ifs);

    cout << "Enter word to look for, q to quit.\n";
    string word;
    while(cout << ">> " && cin >> word && word!="q"){
        print(cout, tq.query(word)) << endl;
    }
}
