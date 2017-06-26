// ex6.54.cpp - Write a declaration for a function that takes two  int
// parameters and returns an  int , and declare a  vector whose elements have
// this function pointer type.
#include <iostream>
#include <vector>
#include <functional>


int addints(int a, int b) { return a+b; }
int subints(int a, int b) { return a - b; }
int multints(int a, int b) { return a * b; }
int divints(int a, int b) { return a / b; }


int main()
{
    using std::cout;
    using std::endl;
    using std::vector;
    using std::function;


    vector<int(*)(int,int)> vfpiii{addints, subints, multints, divints};
    vector<function<int(int,int)>> vfunc{addints, subints, multints, divints,
                                    [](int a,int b)->int
                                    {cout<<"I'm a lambda! a+b = ";return a+b;}
                                    };
    cout << "vector<int(*)(int,int)>:\n";
    for(auto f=vfpiii.begin(); f!=vfpiii.end(); ++f){
        cout << (*f)(42, 11) << '\n';
    }
    cout << "\nvector<function<int(int,int)>>:\n";
    for(auto f=vfunc.cbegin(); f!=vfunc.cend(); ++f){
        cout << (*f)(42, 11) << '\n';
    }
}
