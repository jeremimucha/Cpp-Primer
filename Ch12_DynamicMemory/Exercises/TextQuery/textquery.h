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


class QueryResult;
class TextQuery
{
public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream&);
    QueryResult query(const std::string& s) const;
private:
    std::shared_ptr<std::vector<std::string>> file;  // input file
    // map of each word to the set of the lines in which that word appears
    std::map<std::string,
             std::shared_ptr<std::set<line_no>>> wm;
};


class QueryResult
{
friend std::ostream& print(std::ostream&, const QueryResult&);
public:
    using line_no = TextQuery::line_no;
    QueryResult(std::string s,
                std::shared_ptr<std::set<line_no>> p,
                std::shared_ptr<std::vector<std::string>> f)
        : sought(s), lines(p), file(f)
        { }
private:
    std::string sought;     // word this query represents
    std::shared_ptr<std::set<line_no>> lines;    // lines it's on
    std::shared_ptr<std::vector<std::string>> file; // input file
};

std::ostream& print(std::ostream& os, const QueryResult& qr);

#endif /*TEXTQUERY_H_*/
