// ex12.6
/*Write a function that returns a dynamically allocated
vector of  int s. Pass that  vector to another function that reads the standard
input to give values to the elements. Pass the  vector to another function to
print the values that were read. Remember to  delete the  vector at the
appropriate time.*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::istringstream;
using std::string;
using std::getline;


#define DEBUG_FUNC_ENTRY \
    std::cerr << "Entering <" << __func__ << ">\n"

#define DEBUG_FUNC_EXIT \
    std::cerr << "Exiting <<" << __func__ << ">\n"


vector<int>* vector_factory();
void fill_vector(vector<int>* pvi);
void print_vector(vector<int>* pvi);


int main()
{
    vector<int>* pvi = vector_factory();
    fill_vector(pvi);
    print_vector(pvi);
    delete pvi;
}


vector<int>* vector_factory()
{
    return new vector<int>();
}

void fill_vector(vector<int>* pvi)
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

void print_vector(vector<int>* pvi)
{
    cout << "Here are your integers:\n";
    for( vector<int>::const_iterator it=pvi->cbegin(); it!=pvi->cend(); ){
        cout << *it;
        if( ++it != pvi->end() )
            cout << ", ";
    }
}
