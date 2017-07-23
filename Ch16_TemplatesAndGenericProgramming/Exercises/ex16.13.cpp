/* Exercise 16.14: Write a  Screen class template that uses nontype
parameters to define the height and width of the  Screen. */
#include <iostream>
using std::cout;
using std::endl;


template<unsigned H, unsigned W>
class Screen
{
public:
    Screen() = default;
    Screen(char c)
        {
            for(std::size_t row=0; row<H;++row){
                for(std::size_t col=0; col<W; ++col)
                    screen[col][row] = c;
            }
        }
    void draw() const;

    char screen[W][H];
};


template<unsigned H, unsigned W>
void Screen<H,W>::draw() const
{
    for(std::size_t i=0; i<H; ++i){
        for(std::size_t j=0; j<W; ++j)
            std::cout << screen[j][i];
        std::cout << "\n";
    }
}


int main()
{
    Screen<20,40> s('A');
    s.draw();
}
