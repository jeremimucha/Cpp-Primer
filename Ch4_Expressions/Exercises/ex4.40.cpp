// ex4.40.cpp -- Ch4 Expressions - sizeof operator
#include <iostream>
#include <memory>


int f()
{
    return 1;
}


struct bla
{
    char* mem;
    explicit bla(int i)
        : mem{new char[i]}
        { }
    bla(const bla&) = delete;
    bla(bla&&) = delete;
    bla& operator=(const bla&) = delete;
    bla& operator=(bla&&) = delete;
    ~bla() { delete[] mem; }
};


int main()
{
    using std::cout;
    using std::endl;

    int a = 9;
    int b = 17;
    int x = 42;
    long y = 11;
    std::unique_ptr<bla> p(new bla(42));
    int i = 9;
    cout << "sizeof x + y = " << sizeof x + y << endl;
    cout << "sizeof p = " << sizeof p << endl;
    cout << "sizeof p->mem[i] = " << sizeof p->mem[i] << endl;
    cout << "sizeof a < b = " << (sizeof a < b) << endl;
    cout << "sizeof f() = " << sizeof f() << endl;
    cout << "sizeof void(*)() = " << sizeof (void(*)()) << endl;
}
