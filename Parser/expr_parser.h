#ifndef _PARSER_H_
#define _PARSER_H_

#include "../Lexer/expr_lexer.h"

class Parser {
public:
    Parser(ExprLexer& lexer): lexer(lexer){}
    void parse();
    void program();
    void subtypes_sections();
    void subtype_decl();
    void variable_section();
    void variable_decl();
    void type();
    void array_type();
    void subprogram_decl();
    void subprogram_header();
    void function_header();
    void procedure_header();
    void argument_decl();
    void statement();
    void if_statement();// Implementar
    void else_if_block();
    void else_block();
    void argument();
    void lvalue();
    void lvalue_p();
    void expr();
    void expr_p();
    void expr_p2();
    void bin_op();
    void arith_op();
    void rel_op();
    void eq_op();
    void cond_op();
    void constant();
    void bool_constant();
    Token getToken(){return curr_token;}

private:
    ExprLexer& lexer;
    Token curr_token;
    template<typename T>
    bool checkTk(T tk) {
        return (curr_token == tk);
    }
    template<typename T, typename... TArgs>
    bool checkTk(T token_f, TArgs... moreTk) {
        return (curr_token == token_f) || checkTk(moreTk...);
    }
};

#endif // _PARSER_H_
