/* Exercise 14.50: Show the possible class-type conversion sequences for
the initializations of  ex1 and  ex2 . Explain whether the initializations are legal
or not.
Code:
struct LongDouble {
LongDouble(double = 0.0);
operator double();
operator float();
};
LongDouble ldObj;
int ex1 = ldObj;
float ex2 = ldObj;
Exercise 14.51: Show the conversion sequences (if any) needed to call
each version of  calc and explain why the best viable function is selected.
Code:
void calc(int);
void calc(LongDouble);
double dval;
calc(dval); // which calc?
*/
#include <iostream>


struct LongDouble
{
    LongDouble(double d = 0.0)
        : val(d) { }
    operator double() { return val; }
    operator float() { return val; }
    double val;
};


void calc(int) { std::cout << "calc(int)\n"; }
void calc(LongDouble) { std::cout << "calc(LongDouble)\n"; }


int main()
{
    double dval = 3.14;
    LongDouble ldObj;
    // int ex1 = ldObj;        // ambiguous
    float ex2 = ldObj;         // legal
    calc(dval);                // calc(int) - build-in conversions have precedence?
}
