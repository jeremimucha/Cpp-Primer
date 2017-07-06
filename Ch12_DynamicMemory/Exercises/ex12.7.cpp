// ex12.7
/*Write a function that returns a dynamically allocated
vector of  int s. Pass that  vector to another function that reads the standard
input to give values to the elements. Pass the  vector to another function to
print the values that were read. Use shared_ptr.*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::istringstream;
using std::string;
using std::getline;
using std::shared_ptr;
using std::make_shared;


shared_ptr<vector<int>> vector_factory();
void fill_vector(shared_ptr<vector<int>> pvi);
void print_vector(shared_ptr<vector<int>> pvi);


int main()
{
    shared_ptr<vector<int>> pvi = vector_factory();
    fill_vector(shared_ptr<vector<int>>(pvi));  // legal but unnecessary
    print_vector(pvi);
}


shared_ptr<vector<int>> vector_factory()
{
    return make_shared<vector<int>>();
}

void fill_vector(shared_ptr<vector<int>> pvi)
{
    string line;
    istringstream iss;
    cout << "Enter some integers (empty line to stop).\n";
    while( cout << ">> " && getline(cin, line) && !line.empty() ){
        iss.str(line);
        for( int i; iss >> i; )
            pvi->push_back(i);
        if( iss.fail() && !iss.eof() )
            cout << "Hey, watch it! I said ints only!\n";
        iss.clear();
    }
}

void print_vector(shared_ptr<vector<int>> pvi)
{
    cout << "Here are your integers:\n";
    for( vector<int>::const_iterator it=pvi->cbegin(); it!=pvi->cend(); ){
        cout << *it;
        if( ++it != pvi->end() )
            cout << ", ";
    }
}
