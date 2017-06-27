// screen.h -- Chapter 7 Classes - screen class
#ifndef SCREEN_H_
#define SCREEN_H_

#include <string>
#include <vector>
#include "window_mgr.h"

class Screen
{
public:
    typedef std::string::size_type pos;
    Screen() = default;
    Screen(pos ht, pos wd, char c)
        : height(ht), width(wd), contents(ht*wd, c)
        { }
    // Screen(pos ht, pos wd)
    //     : height(ht), width(wd), contents(ht*wd, ' ')
    //     { }
    Screen(pos ht, pos wd)
        : Screen(ht, wd, ' ')
        { }
    char get() const
        { return contents[cursor]; }
    inline char get(pos r, pos c) const;  // explicitly declare
    Screen& move(pos r, pos c); // can be made inline on member definition
    Screen& set(char);
    Screen& set(pos, pos, char);
    // display overloaded on whether the object is const or not
    Screen& display(std::ostream& os)
        { do_display(os); return *this; }
    const Screen& display(std::ostream& os) const
        { do_display(os); return *this; }
private:
// function to do the work of displaying a Screen
    void do_display(std::ostream& os) const { os << contents; }
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;

// friends
friend void Window_mgr::clear(ScreenIndex);
};

inline Window_mgr::Window_mgr()
    : screens{Screen(24, 80, ' ')}
    { }

void Window_mgr::clear(ScreenIndex i)
{
    // s is a reference to Screen we want to clear
    Screen& s = screens[i];
    s.contents = std::string(s.height * s.width, ' ');
}

char Screen::get(pos r, pos c) const        // declared inline in class
{
    pos row = r * width;    // compute row location
    return contents[row + c];
}

inline
Screen& Screen::move(pos r, pos c)
{
    pos row = r * width;
    cursor = row + c;
    return *this;
}

inline Screen& Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}

inline Screen& Screen::set(pos r, pos col, char ch)
{
    contents[r*width + col] = ch;
    return *this;
}

#endif /*SCREEN_H_*/
