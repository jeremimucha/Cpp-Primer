// Chapter 15 -- Object oriented programming
// Alternate implementation using a Query_base* members for the
// NotQuery, BinaryQuery, AndQuery and OrQuery classes
// Changes include 
// - changing the operand member types from Query to Query_base*,
// - adding a get() member to the Query class. which returns the contained pointer
// - changing constructors to call the get() member during initialization.
// - making NotQuery and BinaryQuery friends to the Query_base class
// - adding use count control to the Query_base class Not the best choice!
// The implementation with use count control within the Query class is much
// cleaner -- see query.h
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
        : use(new std::size_t(1))
    { info("Query_base()"); }
    Query_base(const Query_base& q)
        : use(q.use)
        { ++*use; info("Query_base(const Query&)"); }
    Query_base(Query_base&& q) noexcept
        : use(std::move(q.use))
        { q.use = nullptr; info("Query_base(Query_base&&"); }
    Query_base& operator=(const Query_base&) noexcept;
    Query_base& operator=(Query_base&&) noexcept;
    friend void swap(Query_base& lhs, Query_base& rhs) noexcept;
    virtual ~Query_base()
        {
            info("~Query_base()");
            if(use == 0)
                delete use;
        }

    void info(const char* str) const
        {
            std::cout << str << ": " << reinterpret_cast<const void*>(this)
                << ", use: " << reinterpret_cast<void*>(use)
                << ", *use: " << *use << std::endl;
        }
// --- member variables
    std::size_t* use;

public:
    std::size_t& operator++()
        { return ++*use; }
    std::size_t& operator--()
        { return --*use; }
private:
    // eval returns the QueryResult that matches this Query
    virtual QueryResult eval(const TextQuery&) const = 0;
    // rep is a string representation of the query
    virtual std::string rep() const = 0;


};

inline Query_base& Query_base::operator=(const Query_base& rhs) noexcept
{
    if(use == 0)
        delete use;
    use = rhs.use;
    info("operator=(const Query_base&)");
    return *this;
}
inline Query_base& Query_base::operator=(Query_base&& rhs) noexcept
{
    if(use == 0)
        delete use;
    use = std::move(rhs.use);
    rhs.use = nullptr;
    info("operator=(Query_base&&)");
    return *this;
}
inline void swap(Query_base& lhs, Query_base& rhs) noexcept
{
    using std::swap;
    swap(lhs.use, rhs.use);
}
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
    Query(const Query& query) noexcept
        : pq(query.pq)
        { ++*query.pq;  // increase use count for pq
        info("Query(const Query&)"); }

    Query(Query&& query) noexcept
        : pq(std::move(query.pq))
        { query.pq = nullptr;
            info("Query(Query&&)"); }

    Query& operator=(const Query& rhs);
    Query& operator=(Query&& rhs) noexcept;
    Query_base* get() const
        { return pq; }
    ~Query()
        {
            info("~Query())");
            if( --*pq == 0 )
                delete pq;
        }

    // interface functions: call th ecorresponding Query_base operations
    QueryResult eval(const TextQuery& t) const
        { return pq->eval(t); }
    std::string rep() const
        { std::cout << "Query::rep()" << std::endl;
            return pq->rep(); }

private:
    Query(Query_base* pquery)
        : pq(pquery)
        { ++*pq; info("Query(Query_base*)"); }
// --- member variables
    Query_base* pq;
// -- debug method
    void info(const char* str)
        {
            std::cout << str << ", pq: " << reinterpret_cast<void*>(pq)
                      << std::endl;
        }
};

inline Query& Query::operator=(const Query& rhs)
{
    // protect against self-asignment by incrementing the use count first
    ++*rhs.pq;
    if(--*pq == 0)
        delete pq;
    pq = rhs.pq;

    info("operator=(const Query&)");
    return *this;
}
inline Query& Query::operator=(Query&& rhs) noexcept
{
    if(this == &rhs)
        return *this;
    if( --*pq == 0 )
        delete pq;
    pq = std::move(rhs.pq);
    rhs.pq = nullptr;
    info("operator=(Query&&)");
    return *this;
}

inline void swap(Query& lhs, Query& rhs) noexcept
{
    using std::swap;
    swap(lhs.pq, rhs.pq);
}
/* ------------------------------------------------------------------------- */


/* WordQuery */
/* ------------------------------------------------------------------------- */
class WordQuery : public Query_base
{
    friend class Query;     // Query uses the WordQuery constructor
    WordQuery(const std::string& s)
        : query_word(s)
        { info("WordQuery(const string&)"); }
    
    WordQuery(const WordQuery& wq)
        : Query_base(wq), query_word(wq.query_word)
        { info("WordQuery(const WordQuery&)"); }
    WordQuery(WordQuery&& wq) noexcept
        : Query_base(std::move(wq)), query_word(std::move(wq.query_word))
        { info("WordQuery(WordQuery&&)"); }
    WordQuery& operator=(const WordQuery&);
    WordQuery& operator=(WordQuery&&) noexcept;
    ~WordQuery()
        { info("~WordQuery()"); --*use; }
    // concrete class: WordQuery defines all inherited pure virtual functions
    QueryResult eval(const TextQuery& t) const
        { return t.query(query_word); }
    std::string rep() const
        { std::cout << "WordQuery::rep()" << std::endl;
            return query_word; }
// ---
    std::string query_word;     // word for which to search
};

WordQuery& WordQuery::operator=(const WordQuery& rhs)
{
    ++*rhs.use;
    --*use;
    Query_base::operator=(rhs);
    query_word = rhs.query_word;
    info("operator=(const WordQuery&)");
    return *this;
}
WordQuery& WordQuery::operator=(WordQuery&& rhs) noexcept
{
    if(this == &rhs)
        return *this;
    --*use;
    Query_base::operator=(std::move(rhs));
    query_word = std::move(rhs.query_word);
    info("operator=(WordQuery&&)");
    return *this;
}
/* ------------------------------------------------------------------------- */


/* Query */
/* ------------------------------------------------------------------------- */
inline
Query::Query(const std::string& s)
    : pq(new WordQuery(s)) // pq.use initialized to 1
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
        : pquery(q.get())
        { ++*pquery; // increase use count for pquery
            info("NotQuery(const Query &q)"); }
    NotQuery(const NotQuery&) = delete;
    NotQuery(NotQuery&&) = delete;
    NotQuery& operator=(const NotQuery&) = delete;
    NotQuery& operator=(NotQuery&&) = delete;
    ~NotQuery()
        { info("~NotQuery()"); 
            --*use;
            --*pquery; }
    // concrete class: NotQuery defines all inherited pure virtual functions
    std::string rep() const
        { std::cout << "NotQuery::rep()" << std::endl;
            return "~(" + pquery->rep() + ")"; }
    QueryResult eval(const TextQuery&) const;

// ---
    // std::shared_ptr<Query_base> query;
    Query_base* pquery;
};

inline
Query operator~(const Query& operand)
{
    return new NotQuery(operand);
}
/* ------------------------------------------------------------------------- */

/* BinaryQuery */
/* ------------------------------------------------------------------------- */
class BinaryQuery : public Query_base
{
protected:
    BinaryQuery(const Query& left, const Query& right, std::string s)
        : lhs(left.get()), rhs(right.get()), opSym(s)
        { ++*lhs; ++*rhs; // increase use count for lhs and rhs Query_base*
            info("BinaryQuery(const Query&, const Query&, string)"); }
    BinaryQuery(const BinaryQuery&) = delete;
    BinaryQuery(BinaryQuery&&) = delete;
    BinaryQuery& operator=(const BinaryQuery&) = delete;
    BinaryQuery& operator=(BinaryQuery&&) = delete;
    ~BinaryQuery()
        { info("~BinaryQuery()"); 
            --*use;         // decrease use count for self and pointed to queries
            --*lhs; --*rhs;
        }
    std::string rep() const
        { std::cout << "BinaryQuery::rep()" << std::endl;
            return "(" + lhs->rep() + " "
                       + opSym + " "
                       + rhs->rep() + ")"; }
    
// ---
    Query_base *lhs, *rhs;
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
        { info("AndQuery(const Query&, const Query&)"); }
// concrete class: AndQuery inherits rep and defines the remaining pure virtual
    QueryResult eval(const TextQuery&) const;
};

inline
Query operator&(const Query& lhs, const Query& rhs)
{
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
        { info("OrQuery(const Query&, const Query&)"); }

    QueryResult eval(const TextQuery&) const;
};

inline
Query operator|(const Query& lhs, const Query& rhs)
{
    return new OrQuery(lhs, rhs);
}
/* ------------------------------------------------------------------------- */


#endif /* QUERY_ALT_H_ */
