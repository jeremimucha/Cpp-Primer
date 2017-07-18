#include "query.h"


/* Query_base */
/* ------------------------------------------------------------------------- */
std::string Query_base::rep() const
{ }
/* ------------------------------------------------------------------------- */


/* Query */
/* ------------------------------------------------------------------------- */
std::ostream&
operator<<(std::ostream& os, const Query& query)
{
    // Query::rep makes a virtual call through its Query_base pointer to rep()
    return os << query.rep();
}
/* ------------------------------------------------------------------------- */
