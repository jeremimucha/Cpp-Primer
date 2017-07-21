/* Chapter 15 -- Object oriented programming
 * Exercise 15.41
 * Reimplement your classes to use built-in pointers to
 * Query_base rather than  shared_ptr s. Remember that your classes will no
 * longer be able to use the synthesized copy-control members.
 */
 #ifndef QUERY_H_
 #define QUERY_H_

#include <string>
#include <memory>
#include <utility>
#include "textquery.h"


/* Query_base */
/* ------------------------------------------------------------------------- */
class Query_base
{
    friend class Query;

protected:
    using line_no = TextQuery::line_no;
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
/* ------------------------------------------------------------------------- */
class Query
{
// these operators need access to the Query_base* constructor
    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
    friend void swap(Query& lhs, Query& rhs) noexcept;
public:
    Query(const std::string&);  // builds a new WordQuery
    // interface functions: call th ecorresponding Query_base operations
    QueryResult eval(const TextQuery& t) const
        { return pq->eval(t); }
    std::string rep() const
        { std::cout << "Query::rep()" << std::endl;
            return pq->rep(); }
    Query(const Query& query) noexcept
        : pq(query.pq), use(query.use)
        { ++*use;
            info("Query(const Query&)"); }

    Query(Query&& query) noexcept
        : pq(std::move(query.pq)), use(std::move(query.use))
        { query.pq = nullptr;
          query.use = nullptr;
            info("Query(Query&&)"); }

    Query& operator=(const Query& rhs);
    Query& operator=(Query&& rhs) noexcept;

    ~Query()
        {
            info("~Query())");
            if( --*use == 0 ){
                delete pq;
                delete use;
            }
        }

private:
    Query(Query_base* pquery)
        : pq(pquery), use(new std::size_t(1))
        { info("Query(Query_base*)"); }
// --- member variables
    Query_base* pq;
    std::size_t* use;
// --- debug function
    void info(const char* str)
        {
            std::cout << str << ", pq: " << reinterpret_cast<void*>(pq)
                      << ", *use: " << *use << std::endl;
        }
};

inline Query& Query::operator=(const Query& rhs)
{
    // protect against self-asignment by incrementing the use count first
    ++*rhs.use;
    if(--*use == 0){
        delete pq;
        delete use;
    }
    pq = rhs.pq;
    use = rhs.use;

    info("operator=(const Query&)");
    return *this;
}
inline Query& Query::operator=(Query&& rhs) noexcept
{
    if(this == &rhs)
        return *this;
    if( --*use == 0 ){
        delete pq;
        delete use;
    }
    pq = std::move(rhs.pq);
    use = std::move(rhs.use);
    rhs.pq = nullptr;
    rhs.use = nullptr;
    info("operator=(Query&&)");
    return *this;
}

inline void swap(Query& lhs, Query& rhs) noexcept
{
    using std::swap;
    swap(lhs.pq, rhs.pq);
    swap(lhs.use, rhs.use);
}
/* ------------------------------------------------------------------------- */

/* WordQuery */
/* ------------------------------------------------------------------------- */
class WordQuery : public Query_base
{
    friend class Query;     // Query uses the WordQuery constructor
    WordQuery(const std::string& s)
        : query_word(s)
        { std::cout << "WordQuery(const string&)" << std::endl; }
    
    QueryResult eval(const TextQuery& t) const
        { return t.query(query_word); }
    std::string rep() const
        { std::cout << "WordQuery::rep()" << std::endl;
            return query_word; }
// ---
    std::string query_word;
};
/* ------------------------------------------------------------------------- */

/* Query */
/* ------------------------------------------------------------------------- */
inline
Query::Query(const std::string& s)
    : pq(new WordQuery(s)), use(new std::size_t(1))
{
    info("Query(const string&)");
}
/* ------------------------------------------------------------------------- */

/* NotQuery */
/* ------------------------------------------------------------------------- */
class NotQuery : public Query_base
{
    friend Query operator~(const Query&);
    NotQuery(const Query& q)
        : query(q)
        { std::cout << "NotQuery(const Query&)" << std::endl; }
    ~NotQuery() = default;
    std::string rep() const
        { std::cout << "NotQuery:rep()" << std::endl; 
            return "~(" + query.rep() + ")"; }
    QueryResult eval(const TextQuery&) const;
// --- member variables
    Query query;
};

inline
Query operator~(const Query& operand)
{
    // calls a Query(Query_base*) ctor
    // NotQuery* is implicitly converted to Base_query*
    return new NotQuery(operand);
}
/* ------------------------------------------------------------------------- */


/* BinaryQuery */
/* ------------------------------------------------------------------------- */
class BinaryQuery : public Query_base
{
protected:
    BinaryQuery(const Query& l, const Query& r, std::string s)
        : lhs(l), rhs(r), opSym(s)
        { std::cout << "BinaryQuery(const Query&, const Query&, string&)" 
                    << std::endl; }

    ~BinaryQuery() = default;

    // abstract class: BinaryQuery doesn't define eval
    std::string rep() const
        { std::cout << "BinaryQuery::rep()" << std::endl;
            return "(" + lhs.rep() + " "
                     + opSym + " "
                     + rhs.rep() + ")"; }
// --- member variables
    Query lhs, rhs;     // right-and left-hand operands
    std::string opSym;  // name of the operator
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
    ~AndQuery() = default;
// concrete class: AndQuery inherits rep and defines the remaining pure virtual
    QueryResult eval(const TextQuery&) const;
};

inline
Query operator&(const Query& lhs, const Query& rhs)
{
    // calls Query(Base_query*) ctor
    // AndQuery* is implicitly converted to Base_query*
    return new AndQuery(lhs, rhs);
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
    ~OrQuery() = default;

    QueryResult eval(const TextQuery&) const;
};

inline
Query operator|(const Query& lhs, const Query& rhs)
{
    // calls Query(Base_query*) ctor
    // OrQuery* is implicitly converted to Base_query*
    return new OrQuery(lhs, rhs);
}
/* ------------------------------------------------------------------------- */

 #endif /* QUERY_H_ */
