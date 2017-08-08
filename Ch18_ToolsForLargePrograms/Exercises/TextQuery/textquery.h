#ifndef TEXTQUERY_H_
#define TEXTQUERY_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <utility>



class TextQuery
{
public:
    class QueryResult;
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream&);
    QueryResult query(const std::string& s) const;
private:
    std::shared_ptr<std::vector<std::string>> file;  // input file
    // map of each word to the set of the lines in which that word appears
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;

    static const char* whitespace;
    static std::string& trim(std::string& str);
};


class TextQuery::QueryResult
{
friend std::ostream& print(std::ostream&, const QueryResult&);
public:
// no need to define line_no - public members of a nesting class
    // using line_no = TextQuery::line_no;
    QueryResult(std::string s,
                std::shared_ptr<std::set<line_no>> p,
                std::shared_ptr<std::vector<std::string>> f);
                
    std::set<line_no>::iterator begin()
        { return lines->begin(); }
    std::set<line_no>::iterator end()
        { return lines->end(); }
    std::set<line_no>::const_iterator cbegin() const
        { return lines->cbegin(); }
    std::set<line_no>::const_iterator cend() const
        { return lines->cend(); }
    std::shared_ptr<std::vector<std::string>> get_file()
        { return file; }
private:
    std::string sought;     // word this query represents
    std::shared_ptr<std::set<line_no>> lines;    // lines it's on
    std::shared_ptr<std::vector<std::string>> file; // input file
};

inline
TextQuery::QueryResult::QueryResult(std::string s,
                        std::shared_ptr<std::set<line_no>> p,
                        std::shared_ptr<std::vector<std::string>> f)
    : sought(s), lines(p), file(f)
{
}

std::ostream& print(std::ostream& os, const TextQuery::QueryResult& qr);

#endif /*TEXTQUERY_H_*/
