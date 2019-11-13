#ifndef _EXPR_LEXER_H
#define _EXPR_LEXER_H

#include "expr_tokens.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>

class ExprLexer {
public:
    ExprLexer(std::istream &in) : in(in) {}
    ~ExprLexer() {}
    Token getNextToken();
    Token findKeyWord(std::string text);
    std::string getText() { return text; }

private:
    int getNextChar(){return in.get();}
    void ungetChar(int ch){in.unget();}
    void reportError(int ch) {std::cerr << "Caracter desconocido : " << char(ch) << "\n";}

private:
    std::istream &in;
    std::string text;
};

#endif
