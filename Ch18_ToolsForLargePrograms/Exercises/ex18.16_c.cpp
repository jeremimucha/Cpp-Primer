/* Exercise 18.16: Explain the following code assuming  using declarations
for all the members of namespace  Exercise are located at the location
labeled  position 1. What if they appear at  position 2 instead? Now answer
the same question but replace the  using declarations with a  using directive
for namespace  Exercise .
Code:
namespace Exercise {
int ivar = 0;
double dvar = 0;
const int limit = 1000;
}
int ivar = 0;
// position 1
void manip() {
// position 2
double dvar = 3.1416;
int iobj = limit + 1;
++ivar;
++::ivar;
}
Exercise 18.17: Write code to test your answers to the previous question. */
#include <iostream>
using std::cout;
using std::endl;


namespace Exercise
{
    int ivar = 0;
    double dvar = 0;
    const int limit = 1000;
}

int ivar = 0;
using namespace Exercise;   // Exercise::ivar will hide global ivar
                            // global ivar accessible via ::ivar
void manip()
{
    double dvar = 3.1416;   // local declaration - hides (now global) dvar
    int iobj = limit + 1;
    ++Exercise::ivar;       // must name namespace explicitly to avoid ambeguity
    ++::ivar;       // global scope ivar - explicit
}


int main()
{
    cout << "Before calling manip:\n";
    cout << "\tExercise::ivar: " << Exercise::ivar << "\n"
         << "\t::ivar: " << ::ivar << "\n"
         << "\tdvar: " << Exercise::dvar << "\n"
         << "\tlimit: " << Exercise::limit << "\n";

    manip();

    cout << "\nAfter calling manip:\n";
    cout << "\tExercise::ivar: " << Exercise::ivar << "\n"
         << "\t::ivar: " << ::ivar << "\n"
         << "\tdvar: " << Exercise::dvar << "\n"
         << "\tlimit: " << Exercise::limit << "\n";
}
