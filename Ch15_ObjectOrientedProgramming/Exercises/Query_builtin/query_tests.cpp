#include <iostream>
#include <fstream>
#include "query_alt.h"


int main(int argc, char* argv[])
{
    Query q = Query("fiery") | Query("Two") & Query("Three");
    std::cout << q.rep() << std::endl;
    
    // std::ifstream ifs{argv[1]};
    // if(!ifs.is_open()){
    //     std::cerr << "Failed to open the file: " << argv[1] << std::endl;
    //     exit(EXIT_FAILURE);
    // }

    // TextQuery text(ifs);
    // QueryResult result = q.eval(text);
    // print(std::cout, result);
}
