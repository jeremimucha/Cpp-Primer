// ex 13.46
/* Which kind of reference can be bound to the following
initializers?
int f();
vector<int> vi(100);
int? r1 = f();
int? r2 = vi[0];
int? r3 = r1;
int? r4 = vi[0] * f(); */
#include <iostream>
#include <vector>
#include <utility>
using std::cout;
using std::endl;
using std::vector;


int f(){ return 42; }


int main()
{
    vector<int> vi(100);
    
    int&& rv1 =  f();
    // int& lv1 = f();              // illegal
    const int& clv1 = f();          // ok
    
    // int&& rv2 = vi[0];           // illegal
    int&& mrv2 = std::move(vi[0]);  // legal, but we can no longer use the value of v[0]
    int& lv2 = vi[1];               // legal
    const int& clv2 = vi[1];        // legal

    // int&& rv3 = rv1;             // illegal
    int& lv3 = rv1;                 // legal
    const int& clv3 = rv1;          // legal
    int&& mrv3 = std::move(rv1);    // legal, but we can no loger use the value of rv1

    // int& lv4 = vi[1] * f();      // illegal
    const int& clv4 = vi[1] * f();  // legal
    int&& rv4 = vi[1] * f();        // legal

    cout << "int&& rv1: " << rv1 << endl;
    cout << "const int& clv1: " << clv1 << endl;
    cout << "int&& mrv2: " << mrv2 << endl;
    cout << "int& lv2: " << lv2 << endl;
    cout << "const int& clv2: " << clv2 << endl;
    cout << "int& lv3: " << lv3 << endl;
    cout << "const int& clv3: " << clv3 << endl;
    cout << "int&& mrv3: " << mrv3 << endl;
    cout << "const int& clv4: " << clv4 << endl;
    cout << "int&& rv4: " << rv4 << endl;
}
