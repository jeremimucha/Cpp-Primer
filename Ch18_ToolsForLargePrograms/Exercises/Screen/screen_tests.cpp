// screen_tests.cpp -- Chapter 7 Classes - test code for the Screen class
#include <iostream>
#include "screen.h"
using std::cout;
using std::endl;


int main()
{
    Screen myScreen(5, 5, 'X');
    myScreen.move(4,0).set('#').display(std::cout);
    std::cout << "\n";
    myScreen.display(std::cout);
    std::cout << "\n";


    cout << "\nExercise 19.12:\n";
// pc is a pointer to a data member of the Screen class
// This particular data member is of type Screen::pos
// which is a typedef for std::string::size_type
// Screen::get_pcursor() returns a pointer to the
// cursor member, pc points to that member of the Screen class
// but not to actual data yet.
    const Screen::pos Screen::* pc = Screen::get_pcursor();
// .* operator dereferences pc to fetch the cursor member
// of the myScreen object
    Screen::pos position = myScreen.*pc;
    cout << "position: " << position << endl;
    myScreen.move(1,0); // move cursor to the specified position
    cout << "position after myScreen.move(4,0): " << position << endl;
    cout << "myScreen.*pc: " << myScreen.*pc << endl;

    cout << "\nExercise 19.17:\n";
    cout << "Using the Screen::move function, to change cursor positions:\n";
    myScreen.move(3,3);
    cout << "Initial position: " << myScreen.*pc << endl;
    myScreen.move(Screen::FORWARD);
    cout << "After move(Screen::FORWARD): " << myScreen.*pc << endl;
    myScreen.move(Screen::BACK);
    cout << "After move(Screen::BACK): " << myScreen.*pc << endl;
    myScreen.move(Screen::UP);
    cout << "After move(Screen::UP): " << myScreen.*pc << endl;
    myScreen.move(Screen::DOWN);
    cout << "After move(Screen::DOWN): " << myScreen.*pc << endl;

    // Defining pointers to Screen function members
    cout << "\nExercise 19.17:\n";
    cout << "Using pointers to members:\n";
    
    char (Screen::*pmf_c)() const;
    pmf_c = &Screen::get;
    cout << "character at current positions: " << (myScreen.*pmf_c)() << endl;
    
    char (Screen::*pmf_spp)(Screen::pos, Screen::pos) const;
    pmf_spp = &Screen::get;
    cout << "character at position (1, 1): " << (myScreen.*pmf_spp)(1,1) << endl;

    Screen& (Screen::*pmf_sc)(char);
    pmf_sc = &Screen::set;
    cout << "setting char at current position to Q: ";
    (myScreen.*pmf_sc)('Q');
    cout << (myScreen.*pmf_c)() << endl;

    Screen& (Screen::*pmf_os)(std::ostream&);
    pmf_os = &Screen::display;
    cout << "Displaying the Screen:\n";
    (myScreen.*pmf_os)(std::cout);

    const Screen& (Screen::*pmf_cos)(std::ostream&) const;
    pmf_cos = &Screen::display;
    cout << "\nDisplaying the Screen again:\n";
    (myScreen.*pmf_cos)(std::cout);

    const std::string Screen::* pcontents = Screen::get_pcontents();
    cout << "\nUsing contents member of Screen to display:\n";
    cout << myScreen.*pcontents;

    // const Action(pmenu&)[] = get_pmenu();
}
