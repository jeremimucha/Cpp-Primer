// account.cpp -- implementation for account.h
#include "account.h"

// static members can be defined either in-class or outside of class.
// If defined outside of class the 'static' keyword isn't repeated
void Account::rate(double newRate)
{
    interestRate = newRate;
}

// define non-const member variables outside of class body (only)
double Account::interestRate = initRate();