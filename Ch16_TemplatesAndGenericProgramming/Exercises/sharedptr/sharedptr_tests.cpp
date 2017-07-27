#include <iostream>
#include <string>
#include "sharedptr.h"

template class Sharedptr<int>;
template class Sharedptr<double>;


int main()
{
    // Sharedptr<int> spi(new int(42));
    // Sharedptr<int> spi2;
    // spi2 = spi;
    // {
    //     Sharedptr<int> spi3;
    //     spi3 = spi;
    // }
    // spi2.reset(new int(11), [](int* pi)->void
    //     { std::cerr<<"Deleting pointer managed by spi2"<<std::endl; delete pi; });
    // Sharedptr<double> spd(new double[11]{42}, [](double* pd)->void
    //     { std::cerr<<"Deleting array managed by spd"<<std::endl; delete[] pd; });
    Sharedptr<int> spi(new int(42), [](int* pi)
        {std::cerr<<"Deleting object managed by spi "<<*pi<<std::endl; delete pi;});
    Sharedptr<int> spi2(spi);
    Sharedptr<int> spi3;
    spi3 = spi;
    {
        std::cout << "Entering block" <<std::endl;
        Sharedptr<int> spi4;
        spi4 = spi;
    }
    std::cout << "Leaving block" << std::endl;
    spi3.reset(new int(11), [](int* pi)
        {std::cerr<<"Deleting obj managed by spi3 "<<*pi<<std::endl; delete pi;});
}
