#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <sstream>
#include <memory>
#include <cstring>
#include "doctest.h"
#include "expr_lexer.h"

const char *test1 = "0x123 0b01001 0 1234 0xfafb";
const char *test2 = "+ - * ^ < <= <> > >= = ( ) [ ] , :";
const char *test3 = "_identificador96 booleanoId booleano CaRaCtEr entero abrir real";

doctest::String toString(Token tk) {
    switch (tk) {
        case Token::intConstant: return "intConstant";
        case Token::Op_Add: return "Add";
        case Token::Op_Sub: return "Sub";
        case Token::Op_Mul: return "Mult";
        case Token::Op_Pow: return "Power";
        case Token::Op_LT: return "Less Than";
        case Token::Op_Less_OE: return "Less or Equal";
        case Token::Op_Equal_2: return "Equality 2";
        case Token::Op_GT: return "Greater than";
        case Token::Op_Gre_OE: return "Greater or Equal";
        case Token::Op_Equal: return "Equality 1";
        case Token::OpenPar: return "OpenPar";
        case Token::ClosePar: return "ClosePar";
        case Token::OpenBr: return "OpenBrackets";
        case Token::CloseBr: return "CloseBrackets";
        case Token::Coma: return "Coma";
        case Token::Colon: return "Colon";
        case Token::Caracter: return "Caracter";
        case Token::Booleano: return "Booleano";
        case Token::Abrir: return "Abrir";
        case Token::Real: return "Real";
        case Token::Eof: return "Eof";
        default: return "Unknown";
    }
}

TEST_CASE("intConstant") {
    std::istringstream in;

    in.str(test1);
    ExprLexer l(in);

    Token tk = l.getNextToken();
    CHECK( tk == Token::intConstant );
    CHECK( l.getText() == "0x123" );
    tk = l.getNextToken();
    CHECK( tk == Token::intConstant );
    CHECK( l.getText() == "0b01001" );
    tk = l.getNextToken();
    CHECK( tk == Token::intConstant );
    CHECK( l.getText() == "0" );
    tk = l.getNextToken();
    CHECK( tk == Token::intConstant );
    CHECK( l.getText() == "1234" );
    tk = l.getNextToken();
    CHECK( tk == Token::intConstant );
    CHECK( l.getText() == "0xfafb" );
    tk = l.getNextToken();
    CHECK( tk == Token::Eof );
}

TEST_CASE("Operators 1 & 2") {
    std::istringstream in;

    in.str(test2);
    ExprLexer l(in);
    
    Token tk = l.getNextToken();
    CHECK( tk == Token::Op_Add );
    CHECK( l.getText() == "+" );
    tk = l.getNextToken();
    CHECK( tk == Token::Op_Sub );
    CHECK( l.getText() == "-" );
    tk = l.getNextToken();
    CHECK( tk == Token::Op_Mul );
    CHECK( l.getText() == "*" );
    tk = l.getNextToken();
    CHECK( tk == Token::Op_Pow );
    CHECK( l.getText() == "^" );
    tk = l.getNextToken();
    CHECK( tk == Token::Op_LT );
    CHECK( l.getText() == "<" );
    tk = l.getNextToken();
    CHECK( tk == Token::Op_Less_OE );
    CHECK( l.getText() == "<=" );
    tk = l.getNextToken();
    CHECK( tk == Token::Op_Equal_2 );
    CHECK( l.getText() == "<>" );
    tk = l.getNextToken();
    CHECK( tk == Token::Op_GT );
    CHECK( l.getText() == ">" );
    tk = l.getNextToken();
    CHECK( tk == Token::Op_Gre_OE );
    CHECK( l.getText() == ">=" );
    tk = l.getNextToken();
    CHECK( tk == Token::Op_Equal );
    CHECK( l.getText() == "=" );
    tk = l.getNextToken();
    CHECK( tk == Token::OpenPar );
    CHECK( l.getText() == "(" );
    tk = l.getNextToken();
    CHECK( tk == Token::ClosePar );
    CHECK( l.getText() == ")" );
    tk = l.getNextToken();
    CHECK( tk == Token::OpenBr );
    CHECK( l.getText() == "[" );
    tk = l.getNextToken();
    CHECK( tk == Token::CloseBr );
    CHECK( l.getText() == "]" );
    tk = l.getNextToken();
    CHECK( tk == Token::Coma );
    CHECK( l.getText() == "," );
    tk = l.getNextToken();
    CHECK( tk == Token::Colon );
    CHECK( l.getText() == ":" );
    
}

TEST_CASE("Keywords and ID") {
    std::istringstream in;

    in.str(test3);
    ExprLexer l(in);

    Token tk = l.getNextToken();
    CHECK( tk == Token::ID );
    CHECK( l.getText() == "_identificador96" );
    tk = l.getNextToken();
    CHECK( tk == Token::ID );
    CHECK( l.getText() == "booleanoId" );
    tk = l.getNextToken();
    CHECK( tk == Token::Booleano );
    CHECK( l.getText() == "booleano" );
    tk = l.getNextToken();
    CHECK( tk == Token::Caracter );
    CHECK( l.getText() == "CaRaCtEr" );
    tk = l.getNextToken();
    CHECK( tk == Token::Entero );
    CHECK( l.getText() == "entero" );
    tk = l.getNextToken();
    CHECK( tk == Token::Abrir );
    CHECK( l.getText() == "abrir" );
    tk = l.getNextToken();
    CHECK( tk == Token::Real );
    CHECK( l.getText() == "real" );
    tk = l.getNextToken();
    CHECK( tk == Token::Eof );
}