/* Exercise 15.26: Define the  Quote and  Bulk_quote copy-control members to
do the same job as the synthesized versions. Give them and the other
constructors print statements that identify which function is running. Write
programs using these classes and predict what objects will be created and
destroyed. Compare your predictions with the output and continue
experimenting until your predictions are reliably correct. */
#include <iostream>
#include <string>
#include <utility>
#include "quote.h"
using std::cout;
using std::endl;



int main()
{
    Bulk_quote bq1("bulk1", 1.11, 1, 0.1);
    Bulk_quote bq2(bq1);
    {
        Bulk_quote tempbq("bulk2", 6.66, 6, 0.6);
        bq2 = std::move(tempbq);
    }
}
