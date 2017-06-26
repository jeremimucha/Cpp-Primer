// window_mgr.h -- Chapter 7 - window manager / Screen class friendship
#ifndef WINDOW_MGR_H_
#define WINDOW_MGR_H_

#include <iostream>
#include <vector>

class Screen;

class Window_mgr
{
public:
    // location ID for each Screen on the window
    using ScreenIndex = std::vector<Screen>::size_type;
    Window_mgr();
    void clear(ScreenIndex);
private:
    std::vector<Screen> screens;
};


#endif /*WINDOW_MGR_H_*/
