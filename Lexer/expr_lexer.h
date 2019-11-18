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
    void reportError(int ch) {std::cerr << "Error en la linea " << line << " : Caracter desconocido -> " << char(ch) << "\n";}
    void stringError() {std::cerr << "Error en la linea " << line <<" : String contiene 1 o mas fin de linea -> EOL " << "\n";}
    bool ischar(int ch2){ 
        if(ch2 >126 && ch2 <32){
            std::cerr << "Caracer fuera del rango ascii [32 - 126]" << '\n';
            return 0;
        }
        else
            return true;
        }

private:
    std::istream &in;
    std::string text;
    int line = 1;
};

#endif
