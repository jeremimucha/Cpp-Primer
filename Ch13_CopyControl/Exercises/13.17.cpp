// ex 13.17
/*Write versions of  numbered and  f corresponding to the
previous three exercises and check whether you correctly predicted the
output.*/
#include <iostream>
#include <string>
#include <set>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <iomanip>
using std::cout;
using std::endl;
using std::string;
using std::set;
using std::pair;


class numbered
{
public:
    numbered(const string& s)
        : mysn(), data(s)
        {
            int sn = std::rand() % snmax;
            while( taken.find(sn) != taken.cend() ){
                sn = std::rand() % snmax;
            }
            taken.insert(sn);
            mysn = sn;
            cout << "numbered() -> " << mysn << ", " << data << endl;
        }
    numbered(const numbered& rhs)
        : mysn(rhs.mysn), data(rhs.data)
        {
            while( taken.find(++mysn) != taken.cend() )
                ;
            taken.insert(mysn);
            cout << "numbered(const numbered&) -> " << mysn << ", " << data << endl;
        }
    numbered& operator=(const numbered& rhs)
        {
            if(this == &rhs)
                return *this;
            data = rhs.data;
            cout << "operator=(const numbered&) ->" << mysn << ", " 
                 << data << endl;
            return *this;
        }

friend std::ostream& operator<<(std::ostream& os, const numbered& n);
private:
    size_t mysn;
    string data;
    static const size_t snmax{10000};
    static set<int> taken;
};

set<int> numbered::taken{};

std::ostream& operator<<(std::ostream& os, const numbered& n)
{
    return os <<  "SN: " << std::setfill('0') << std::setw(5) << n.mysn
              << ", data: " << n.data;
}


void f(numbered s) { cout << s << endl; }


int main()
{
    std::srand(std::time(nullptr));

    numbered n1("one");
    numbered n2("two");
    numbered n3(n1);
    cout << "assigning n2 = n1:\n";
    n2 = n1;
    cout << "calling f(n1):\n";
    f(n1);
    cout << "n1: " << n1 << "\n"
         << "n2: " << n2 << "\n"
         << "n3: " << n3 << "\n"
         << endl;
}
