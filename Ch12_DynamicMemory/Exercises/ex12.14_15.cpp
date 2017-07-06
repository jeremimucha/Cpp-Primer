// ex12.14
/*
Write your own version of a function that uses a
shared_ptr to manage a  connection .
ex 12.15
Rewrite the first exercise to use a lambda (§ 10.3.2, p.
388) in place of the  end_connection function.
*/
#include <iostream>
#include <string>
#include <memory>
#include <iomanip>
using std::cout;
using std::endl;
using std::string;
using std::shared_ptr;
using std::make_shared;


struct destination
{
    int port;
    bool connected;
};

struct connection
{
    destination* dst;
};

connection connect(destination* d);
void disconnect(connection c);
void f(destination& d);
void f_lambda(destination& d);
void end_connection(connection* c);

int main()
{
    cout.setf(std::ios_base::boolalpha);
    cout << std::showbase;
    destination dest{1234, false};
    f(dest);
    cout << "<main> after f(dest): port = " << dest.port << ", connected = "
         << dest.connected << endl;
    f_lambda(dest);
    cout << "<main> after f_lambda(dest): port = " << dest.port << ", connected = "
    << dest.connected << endl;
}


connection connect(destination* d)
{
    cout << "<connect>: connected to destination " << reinterpret_cast<void*>(d) 
         << ", port = " << d->port << "\n";
    connection c{d};
    c.dst->connected = true;
    return c;
}

void disconnect(connection c)
{
    cout << "<disconnect>: disconnected from destination "
         << reinterpret_cast<void*>(c.dst) << ", port = " << c.dst->port
         << endl;
    c.dst->connected = false;
}

void f(destination& d)
{
    cout << "<f>\n";
    cout << "&d = " << reinterpret_cast<void*>(&d) << "\n";
    cout << "Before calling connect.\n"
         << "d: port = " << d.port << ", connected = " << d.connected
         << endl;

// get a connection; must close it when done
    connection c = connect(&d);
// make a shared_ptr to the connection object to ensure that it's
// properly closed on scope exit
    shared_ptr<connection> spc(&c, end_connection);

    cout << "After calling connect.\n"
         << "&c = " << reinterpret_cast<void*>(&c) << "\n"
         << "d: port = " << d.port << ", connected = " << d.connected
         << endl;
    
// no need to call diconnect(c) manually
// shared_ptr will call end_connection(&c) when it goes out of scope
}

void f_lambda(destination& d)
{
    cout << "<f_lambda>\n";
    cout << "&d = " << reinterpret_cast<void*>(&d) << "\n";
    cout << "Before calling connect.\n"
         << "d: port = " << d.port << ", connected = " << d.connected
         << endl;

// get a connection; must close it when done
    connection c = connect(&d);
// make a shared_ptr to the connection object to ensure that it's
// properly closed on scope exit
// use a lambda as the deleter/destructor
    shared_ptr<connection> spc(&c, [](connection* c)
                            {cout << "<shared_ptr-lambda-destructor> c = "
                                  << reinterpret_cast<void*>(c) << "\n";
                            disconnect(*c);}
                            );

    cout << "After calling connect.\n"
         << "&c = " << reinterpret_cast<void*>(&c) << "\n"
         << "d: port = " << d.port << ", connected = " << d.connected
         << endl;
    
// no need to call diconnect(c) manually
// shared_ptr will call end_connection(&c) when it goes out of scope
}

void end_connection(connection* c)
{
    cout << "<end_connection> c = " << reinterpret_cast<void*>(c) << "\n";
    disconnect(*c);
}
