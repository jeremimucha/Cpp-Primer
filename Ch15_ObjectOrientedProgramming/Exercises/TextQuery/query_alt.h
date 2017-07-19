// Chapter 15 -- Object oriented programming
// Alternate implementation using a shared_ptr<Query_base> members for the
// NotQuery, BinaryQuery, AndQuery and OrQuery classes
// Changes include 
// - changing the operand member types from Query to shared_ptr<Query_base>,
// - adding a get() member to the Query class. which returns the contained shared_ptr,
// - changing constructors to call the get() member during initialization.
// making NotQuery and BinaryQuery friends to the Query_base class
#ifndef QUERY_ALT_H_
#define QUERY_ALT_H_

#include <string>
#include <memory>
#include "textquery.h"


/* Query_base */
/* ------------------------------------------------------------------------- */
class Query_base
{
    friend class Query;
    friend class NotQuery;
    friend class BinaryQuery;
protected:
    using line_no = TextQuery::line_no;     // used in the eval functions
    Query_base()
    { std::cout << "Query_base()" << std::endl; }
    virtual ~Query_base() = default;
private:
    // eval returns the QueryResult that matches this Query
    virtual QueryResult eval(const TextQuery&) const = 0;
    // rep is a string representation of the query
    virtual std::string rep() const = 0;
};
/* ------------------------------------------------------------------------- */


/* Query */
/* interface class to manage the Query_base inheritance hierarchy */
/* ------------------------------------------------------------------------- */
class Query
{
// these operators need access to the shared_ptr constructor
    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
public:
    Query(const std::string&);  // biulds a new WordQuery
    // interface functions: call the corresponding Query_base operations
    QueryResult eval(const TextQuery& t) const
        { return q->eval(t); }
    std::string rep() const
        { std::cout << "Query::rep()" << std::endl;
            return q->rep(); }
    std::shared_ptr<Query_base> get() const
        { return q; }
private:
    Query(std::shared_ptr<Query_base> query)
        : q(query)
        { std::cout << "Query(shared_ptr<Query_base>)" << std::endl; }

// ---
    std::shared_ptr<Query_base> q;
};
/* ------------------------------------------------------------------------- */


/* WordQuery */
/* ------------------------------------------------------------------------- */
class WordQuery : public Query_base
{
    friend class Query;     // Query uses the WordQuery constructor
    WordQuery(const std::string& s)
        : query_word(s)
        { std::cout << "WordQuery(const string&)" << std::endl; }
    // concrete class: WordQuery defines all inherited pure virtual functions
    QueryResult eval(const TextQuery& t) const
        { return t.query(query_word); }
    std::string rep() const
        { std::cout << "WordQuery::rep()" << std::endl;
            return query_word; }

// ---
    std::string query_word;     // word for which to search
};
/* ------------------------------------------------------------------------- */


/* Query */
/* ------------------------------------------------------------------------- */
inline
Query::Query(const std::string& s)
    : q(new WordQuery(s))
{
    std::cout << "Query(const string& = " << s << ")" << std::endl;
}
/* ------------------------------------------------------------------------- */


/* NotQuery */
/* ------------------------------------------------------------------------- */
// class NotQuery : public Query_base
// {
//     friend Query operator~(const Query&);
//     NotQuery(const Query& q)
//         : query(q)
//         { std::cout << "NotQuery(const Query&)" << std::endl; }
//     // concrete class: NotQuery defines all inherited pure virtual functions
//     std::string rep() const
//         { std::cout << "NotQuery::rep()" << std::endl;
//             return "~(" + query.rep() + ")"; }
//     QueryResult eval(const TextQuery&) const;
    
// // ---
//     Query query;
// };

// inline
// Query operator~(const Query& operand)
// {
//     return std::shared_ptr<Query_base>(new NotQuery(operand));
// }
/* ------------------------------------------------------------------------- */

/* NotQuery */
/* ------------------------------------------------------------------------- */
class NotQuery : public Query_base
{
    friend Query operator~(const Query&);
    NotQuery(const Query& q)
        : query(q.get())
        { std::cout << "NotQuery(const Query &q)" << std::endl; }
    // concrete class: NotQuery defines all inherited pure virtual functions
    std::string rep() const
        { std::cout << "NotQuery::rep()" << std::endl;
            return "~(" + query->rep() + ")"; }
    QueryResult eval(const TextQuery&) const;

// ---
    std::shared_ptr<Query_base> query;
};

inline
Query operator~(const Query& operand)
{
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}
/* ------------------------------------------------------------------------- */

/* BinaryQuery */
/* ------------------------------------------------------------------------- */
// class BinaryQuery : public Query_base
// {
// protected:
//     BinaryQuery(const Query& l, const Query& r, std::string s)
//         : lhs(l), rhs(r), opSym(s)
//         { std::cout << "BinaryQuery(const Query&, const Query&, string&)" 
//                     << std::endl; }

//     // abstract class: BinaryQuery doesn't define eval
//     std::string rep() const
//         { std::cout << "BinaryQuery::rep()" << std::endl;
//             return "(" + lhs.rep() + " "
//                      + opSym + " "
//                      + rhs.rep() + ")"; }
    
//     Query lhs, rhs;     // right-and left-hand operands
//     std::string opSym;  // name of the operator
// };
/* ------------------------------------------------------------------------- */


/* BinaryQuery */
/* ------------------------------------------------------------------------- */
class BinaryQuery : public Query_base
{
protected:
    BinaryQuery(const Query& left, const Query& right, std::string s)
        : lhs(left.get()), rhs(right.get()), opSym(s)
        { std::cout << "BinaryQuery(const Query&, const Query&, string)"
                    << std::endl; }

    std::string rep() const
        { std::cout << "BinaryQuery::rep()" << std::endl;
            return "(" + lhs->rep() + " "
                       + opSym + " "
                       + rhs->rep() + ")"; }
    
// ---
    std::shared_ptr<Query_base> lhs, rhs;
    std::string opSym;
};
/* ------------------------------------------------------------------------- */


/* AndQuery */
/* ------------------------------------------------------------------------- */
class AndQuery : public BinaryQuery
{
    friend Query operator&(const Query&, const Query&);
    AndQuery(const Query& left, const Query& right)
        : BinaryQuery(left, right, "&")
        { std::cout << "AndQuery(const Query&, const Query&)" << std::endl; }
// concrete class: AndQuery inherits rep and defines the remaining pure virtual
    QueryResult eval(const TextQuery&) const;
};

inline
Query operator&(const Query& lhs, const Query& rhs)
{
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}
/* ------------------------------------------------------------------------- */


/* OrQuery */
/* ------------------------------------------------------------------------- */
class OrQuery : public BinaryQuery
{
    friend Query operator|(const Query&, const Query&);
    OrQuery(const Query& left, const Query& right)
        : BinaryQuery(left, right, "|")
        { std::cout << "OrQuery(const Query&, const Query&)" << std::endl; }

    QueryResult eval(const TextQuery&) const;
};

inline
Query operator|(const Query& lhs, const Query& rhs)
{
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}
/* ------------------------------------------------------------------------- */


#endif /* QUERY_ALT_H_ */
