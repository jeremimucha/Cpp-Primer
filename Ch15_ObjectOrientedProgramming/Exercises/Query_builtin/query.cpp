#include "query.h"
#include <set>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <iterator>
using std::set;
using std::vector;
using std::string;
using std::shared_ptr;
using std::make_shared;
using std::set_intersection;
using std::inserter;


/* Query_base */
/* ------------------------------------------------------------------------- */
std::string Query_base::rep() const
{ return ""; }
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


/* WordQuery */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */


/* NotQuery */
/* ------------------------------------------------------------------------- */
QueryResult NotQuery::eval(const TextQuery& text) const
{
    // virtual call to eval through the Query operand
    QueryResult result = query.eval(text);
    // start out with an empty result set
    shared_ptr<set<line_no>> ret_lines = make_shared<set<line_no>>();
    // we have to iterato through thel ines on which our operand appears
    set<line_no>::const_iterator beg = result.cbegin()
                                ,end = result.cend();
    // for each line in the input file, if that line is not in result
    // add that line number to ret_lines
    vector<string>::size_type sz = result.get_file()->size();
    for(size_t n = 0; n != sz; ++n){
        // if we haven't processed all the lines in result
        // check whether this line is present
        if(beg == end || *beg != n)
            ret_lines->insert(n);   // if not in result, add this line
        else if(beg != end)
            ++beg;  // otherwise get the next line number in result if there is one
    }
    return QueryResult(rep(), ret_lines, result.get_file());
}
/* ------------------------------------------------------------------------- */


/* AndQuery */
/* ------------------------------------------------------------------------- */
QueryResult AndQuery::eval(const TextQuery& text) const
{
    // virtual calls through the Query operands to get result sets for teh operands
    QueryResult left = lhs.eval(text), right = rhs.eval(text);
    shared_ptr<set<line_no>> ret_lines = make_shared<set<line_no>>();
    // writes the intersection of two ranges to a destination iterator
    // destination iterator in this call adds elements to ret
    set_intersection(left.cbegin(), left.cend(),
                     right.cbegin(), right.cend(),
                     inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines, left.get_file());
}
/* ------------------------------------------------------------------------- */


/* OrQuery */
/* ------------------------------------------------------------------------- */
QueryResult OrQuery::eval(const TextQuery& text) const
{ 
    // virtual calls through the Query members, lhs and rhs
    // the calls to eval return teh QueryResult for each operand
    QueryResult right = rhs.eval(text), left = lhs.eval(text);
    // copy the line numbers from the left-hand operand into the result set
    shared_ptr<set<line_no>> ret_lines =
        make_shared<set<line_no>>(left.cbegin(), left.cend());
    // insert lines from right-hand operand
    ret_lines->insert(right.cbegin(), right.cend());
    // return the new QueryResult representing the union of lhs and rhs
    return QueryResult(rep(), ret_lines, left.get_file());
}
/* ------------------------------------------------------------------------- */
