#include <iostream>
#include <functional>
#include <memory>
#include "uniqueptr.h"

// template class Uniqueptr<int>;
void mydelete(int* pi) { std::cerr<<"mydelete " <<*pi << std::endl; delete pi; }

int main()
{
    Uniqueptr<int,std::function<void(int*)>> ui(new int(42), [](int* pi)
        {std::cerr<<"Deleting obj managed by ui: "<<*pi<<std::endl;delete pi;});
    {
        std::cout << "Entering block."<<std::endl;
        Uniqueptr<int,std::function<void(int*)>> ui2(new int(11), [](int* pi)
            {std::cerr<<"Deleting obj managed by ui2: "<<*pi<<std::endl;delete pi;});
        
        Uniqueptr<int,void(*)(int*)> ui3(new int(3), mydelete);
        Uniqueptr<int,decltype(mydelete)*> ui4(new int(4), mydelete);

        ui.reset(ui2.release());
        ui2.reset(new int(9));
    }
    std::cout << "Left the block."<<std::endl;
    //     std::unique_ptr<int, std::function<void(int*)>> ui(new int(42), [](int* pi)
    //     {std::cerr<<"Deleting obj managed by ui: "<<*pi<<std::endl;delete pi;});
    // {
    //     std::cout << "Entering block."<<std::endl;
    //     std::unique_ptr<int, std::function<void(int*)>> ui2(new int(11), [](int* pi)
    //         {std::cerr<<"Deleting obj managed by ui2: "<<*pi<<std::endl;delete pi;});
        
    //     ui.reset(ui2.release());
    //     ui2.reset(new int(9));
    // }
    // std::cout << "Left the block."<<std::endl;
}