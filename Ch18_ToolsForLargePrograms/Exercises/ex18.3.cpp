/* Exercise 18.2: Explain what happens if an exception occurs at the
indicated point:
Code:
void exercise(int *b, int *e)
{
vector<int> v(b, e);
int *p = new int[v.size()];
ifstream in("ints");
// exception occurs here
}
Exercise 18.3: There are two ways to make the previous code work
correctly if an exception is thrown. Describe them and implement them. */
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <memory>
using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::unique_ptr;
using std::runtime_error;

// ex 18.3
// Options A is to use a try...catch block to free the allocated resources
// and rethrow the exception.
void exercise_a(int* b, int* e);

// ex 18.3
// Option B is to use a smart pointer - a unique_ptr in this case
// as a resource owner responsible for freeing the allocated resources
void exercise_b(int* b, int* e);


struct Deleter
{
    template<typename T>
    void operator()(T* p)
        { std::cerr << "Deleting pointer " 
            << reinterpret_cast<const void*>(p) << std::endl; }
};


int main()
{
    int arr[]{1,2,3,4,5,6,7,8,9};
    try{
        cout << "In main. Executing exercise_a(b, e)\n";
        exercise_a(std::begin(arr), std::end(arr));
    }
    catch(std::exception& e){
        std::cerr << "In main catch block #1\n";
        std::cerr << e.what() << endl;
    }

    try{
        cout << "In main. Executing exercise_b(b, e)\n";
        exercise_b(std::begin(arr), std::end(arr));
    }
    catch(std::exception& e){
        std::cerr << "In main catch block #2\n";
        std::cerr << e.what() << endl;
    }
}


void exercise_a(int* b, int* e)
{
    vector<int> v(b, e);
    int* p = new int[v.size()];
    ifstream in("ints");
    try{
        // do some work that throws an exception
        throw runtime_error("<exercise_a> :: runtime error within the try block");
    }
    catch(std::exception e){
        std::cerr << "<excercise_a> :: catch block - freeing allocated resources and rethrowing.\n";
        delete[] p;
        std::cerr << "Pointer " << reinterpret_cast<const void*>(p) << " deleted, rethrowing...\n";
        throw;
    }
    std::cerr << "<exercise_a> :: This should not be executed!\n";
}

void exercise_b(int* b, int* e)
{
    vector<int> v(b, e);
    unique_ptr<int[], Deleter> up(new int[v.size()], Deleter());
    ifstream in("ints");
    // do some work that throws an exception
    throw runtime_error("<exercise_b> :: runtime error - no try block\n");
    std::cerr << "<exercise_b> :: This should not be executed!\n";
}
