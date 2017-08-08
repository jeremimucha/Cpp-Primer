#include "token.h"
using std::string;

const char* Token::tok_names[]{ "INT"
                              , "CHAR"
                              , "DBL"
                              , "STR"
                              };

void Token::copyUnion(const Token& t)
{
    switch(t.tok){
        case Token::INT:
            ival = t.ival; break;
        case Token::CHAR:
            cval = t.cval; break;
        case Token::DBL:
            dval = t.dval; break;
        case Token::STR:
            new(&sval) string(t.sval); break;
    }
}

void Token::moveUnion(Token&& t)
{
    switch(t.tok){
        case Token::INT:
            ival = t.ival; break;
        case Token::CHAR:
            cval = t.cval; break;
        case Token::DBL:
            dval = t.dval; break;
        case Token::STR:
            new(&sval) string(std::move(t.sval)); break;
    }
}

Token& Token::operator=(const Token& t)
{
    // if this object holds a string and t doesn't,
    // we have to free the old string
    if(tok == STR && t.tok != STR)
        sval.~string();
    if(tok == STR && t.tok == STR)
        sval = t.sval;  // no need to construct a new string
    else
        copyUnion(t);   // will construct a string if t.tok is STR
    tok = t.tok;
    return *this;
}

Token& Token::operator=(Token&& t)
{
    if(tok == STR&& t.tok != STR)
        sval.~string();
    if(tok == STR && t.tok == STR)
        sval = std::move(t.sval);
    else
        moveUnion(std::move(t));
    tok = std::move(t.tok);
    return *this;
}

Token& Token::operator=(int i)
{
    if(tok == STR) sval.~string();
    ival = i;
    tok = INT;
    return *this;
}

Token& Token::operator=(double d)
{
    if(tok == STR) sval.~string();
    dval = d;
    tok = DBL;
    return *this;
}

Token& Token::operator=(char ch)
{
    if(tok == STR) sval.~string();
    cval = ch;
    tok = CHAR;
    return *this;
}

Token& Token::operator=(const std::string& s)
{
    if(tok == STR)  // if we already hold a string, just do an assignment
        sval = s;
    else
        new(&sval) string(s);
    tok = STR;
    return *this;
}

Token& Token::operator=(std::string&& s) noexcept
{
    if(tok == STR)
        sval = std::move(s);
    else
        new(&sval) string(std::move(s));
    tok = STR;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Token& t)
{
    os << "Token: {tok = " << Token::tok_names[t.tok] << ", val = ";
    switch(t.tok){
        case Token::INT: os << t.ival; break;
        case Token::CHAR: os << t.cval; break;
        case Token::DBL: os << t.dval; break;
        case Token::STR: os << t.sval; break;
    }
    os << "}";
    return os;
}
