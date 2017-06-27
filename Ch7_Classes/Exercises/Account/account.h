// account.h -- Chapter 7
#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <string>


class Account
{
public:
    static double rate() { return interestRate; }
    static void rate(double);
    void calculate() { anount += amount *= interestRate; }
private:
    static constexpr int period = 30;   // init constexpressions in class body
    static double interestRate;
    static double initRate();
    double daily_tbl[period];
    std::string owner;
    double amount;
};


#endif /*ACCOUNT_H_*/
