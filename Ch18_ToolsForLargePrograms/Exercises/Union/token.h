#ifndef TOKEN_H_
#define TOKEN_H_

#include <iostream>
#include <string>
#include <utility>


class Token
{
public:
    // copy control needed beacuse our class has a union with a string member
    Token()
        : tok(INT), ival(0) { }
    Token(int i)
        : tok(INT), ival(i) { }
    Token(double d)
        : tok(DBL), dval(d) { }
    Token(char ch)
        : tok(CHAR), cval(ch) { }
    Token(const std::string& s)
        : tok(STR), sval(s) { }
    Token(std::string&& s)
        : tok(STR), sval(std::move(s)) { }
    Token(const Token& t)
        : tok(t.tok) { copyUnion(t); }
    Token(Token&& t)
        : tok(std::move(t.tok)) { moveUnion(std::move(t)); }
    Token& operator=(const Token&);
    Token& operator=(Token&&);
    // if the union holds a string, we must destroy it
    ~Token()
        { using std::string;
            if(tok == STR) sval.~string(); }
    Token& operator=(const std::string&);
    Token& operator=(std::string&& s) noexcept;
    Token& operator=(char);
    Token& operator=(int);
    Token& operator=(double);

friend std::ostream& operator<<(std::ostream& os, const Token& t);
private:
    enum { INT, CHAR, DBL, STR } tok;   // discriminant
    static const char* tok_names[];
    union {
        char    cval;
        int     ival;
        double  dval;
        std::string sval;
    };  // each Token object has an unnamed member of this unnamed union type
    // check the discriminant and copy the union member as appropriate
    void copyUnion(const Token&);
    // check the discriminant and move the union member as appropriate
    void moveUnion(Token&&);
};


#endif /* TOKEN_H_ */
