/* Exercise 19.12: Define a pointer to member that can point to the  cursor
member of class  Screen. Fetch the value of  Screen::cursor through that
pointer. */
#ifndef SCREEN_H_
#define SCREEN_H_

#include <string>
#include <vector>
#include "window_mgr.h"

class Screen
{
public:
    typedef std::string::size_type pos;

// Action is a type alias for pointers to member functions
// of class Screen taking no arguments and returning Screen&
    using Action = Screen& (Screen::*)();
    using ActionGet = char (Screen::*)() const;
    using ActionGet2P = char (Screen::*)(Screen::pos, Screen::pos) const;
    enum Directions { HOME, FORWARD, BACK, UP, DOWN };

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
    Screen& home() noexcept
        { cursor = 0; return *this; }
    Screen& forward() noexcept;
    Screen& back() noexcept;
    Screen& up() noexcept;
    Screen& down() noexcept;
    Screen& move(Directions) noexcept;
    // display overloaded on whether the object is const or not
    Screen& display(std::ostream& os)
        { do_display(os); return *this; }
    const Screen& display(std::ostream& os) const
        { do_display(os); return *this; }

// --- Return a pointer to member 
    static const pos Screen::* get_pcursor() 
        { return &Screen::cursor; }
    static const std::string Screen::* get_pcontents()
        { return &Screen::contents; }
    // static Action(*)[] Screen::* get_pmenu()
    //     { return &Screen::Menu; }
private:
// function to do the work of displaying a Screen
    void do_display(std::ostream& os) const { os << contents; }
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;

    static Action Menu[];   // function table;

// friends
friend void Window_mgr::clear(ScreenIndex);
};

inline Window_mgr::Window_mgr()
    : screens{Screen(24, 80, ' ')}
    { }

inline void Window_mgr::clear(ScreenIndex i)
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

inline Screen& Screen::forward() noexcept
{ 
    if( cursor < width * height - 1 ) ++cursor;
    else cursor = 0;
    return *this;
}
inline Screen& Screen::back() noexcept
{
    if(0 < cursor) --cursor;
    else cursor = width * height - 1;
    return *this;
}
inline Screen& Screen::up() noexcept
{
    if( cursor / width > 0 ) cursor -= width;
    return *this;
}
inline Screen& Screen::down() noexcept
{
    pos newpos = cursor + width;
    if( newpos < width * height - 1)
        cursor = newpos;
    return *this;
}

inline Screen& Screen::move(Directions cm) noexcept
{
    // run the element indexed by cm on this object
    // Menu[cm] accesses a pointer to a member function
    // at index cm this pointer is then dereferenced on
    // this object - calling the pointed to member function
    return (this->*Menu[cm])();
}

#endif /*SCREEN_H_*/
