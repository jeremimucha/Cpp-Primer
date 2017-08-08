#include <iostream>
#include <string>
#include "token.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;


int main()
{
    Token ts("string");
    Token ti(42);
    Token tc('C');
    Token td(4.2);
    cout << "ts: " << ts << endl;
    cout << "ti: " << ti << endl;
    cout << "tc: " << tc << endl;
    cout << "td: " << td << endl;
}
