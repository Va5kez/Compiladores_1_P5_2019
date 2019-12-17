#ifndef _PARSER_H_
#define _PARSER_H_

#include "../Lexer/expr_lexer.h"
#include "../AST/expr_ast.h"

class Parser {
public:
    Parser(ExprLexer& lexer): lexer(lexer){}
    AST *parse();
    AST *program();
    AST *subtypes_sections();
    AST *subtype_decl();
    AST *variable_section();
    AST *variable_decl();
    Types type();
    Types array_type();
    AST *subprogram_decl();
    AST *subprogram_header();
    AST *function_header();
    AST *procedure_header();
    AST *argument_decl();
    AST *statement();
    AST *if_statement();
    AST *else_if_block();
    AST *else_block();
    AST *argument();
    AST *lvalue();
    AST *lvalue_p();
    AST *expr();
    AST * expr_p();
    AST *expr_p2();
    std::string bin_op();
    std::string arith_op();
    std::string rel_op();
    std::string eq_op();
    std::string cond_op();
    std::string constant();
    std::string bool_constant();
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
