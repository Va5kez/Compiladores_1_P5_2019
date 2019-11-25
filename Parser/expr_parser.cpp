#include "expr_parser.h"

void Parser::parse()
{
    curr_token = lexer.getNextToken();
    program();
    if(checkTk(Token::Eof))
        std::cout << "Se llego al final del archivo" << '\n';
    else
        throw "Error en el parser: Sobraron tokens \n";
}
void Parser::program()
{
    if(checkTk(Token::Tipo))
        subtypes_sections();
    if(checkTk(Token::Entero, Token::Booleano, Token::Caracter, Token::Arreglo))
        variable_section();
    if(checkTk(Token::Funcion, Token::Procedimiento))
    {
        subprogram_decl();
        while(checkTk(Token::Funcion, Token::Procedimiento))
        {
            subprogram_decl();
            curr_token = lexer.getNextToken();
            if(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
        }
        if(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
    }
    if(checkTk(Token::Inicio))
    {
        curr_token = lexer.getNextToken();
        if(checkTk(Token::Eol))
            curr_token = lexer.getNextToken();
        if(checkTk(Token::ID, Token::Llamar, Token::Escriba, Token::Lea, Token::Retorne, Token::Si, Token::Mientras, Token::Repita, Token::Para))
        {
            statement();
            while(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
            while(checkTk(Token::ID, Token::Llamar, Token::Escriba, Token::Lea, Token::Retorne, Token::Si, Token::Mientras, Token::Repita, Token::Para))
            {
                statement();
                if(checkTk(Token::Eol))
                    curr_token = lexer.getNextToken();
            }
        }
        while(checkTk(Token::Eol))
            curr_token = lexer.getNextToken();
        if(checkTk(Token::Fin))
        {
            curr_token = lexer.getNextToken();
            if(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
        }
        else
            throw "Program -> Se esperaba Fin pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    }
    else
        throw "Program -> Se esperaba Inicio pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
void Parser::subtypes_sections()
{
    if(checkTk(Token::Tipo))
    {
        subprogram_decl();
        if(checkTk(Token::Eol))
            curr_token = lexer.getNextToken();
        while(checkTk(Token::Tipo))
        {
            curr_token = lexer.getNextToken();
            if(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
        }
    }
}
void Parser::subtype_decl()
{
    if(checkTk(Token::Tipo))
    {
        curr_token = lexer.getNextToken();
        if(checkTk(Token::ID))
        {
            curr_token = lexer.getNextToken();
            if(checkTk(Token::Es))
            {
                curr_token = lexer.getNextToken();
                type();
            }
            else
                throw "Se esperaba Es pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
        }
        else
            throw "Se esperaba ID pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    }
    else
        throw "Se esperaba Tipo pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
void Parser::variable_section()
{
    if(checkTk(Token::Entero, Token::Booleano, Token::Caracter, Token::Arreglo))
    {
        variable_decl();
        curr_token = lexer.getNextToken();
        if(checkTk(Token::Eol))
            curr_token = lexer.getNextToken();
        while(checkTk(Token::Entero, Token::Booleano, Token::Caracter, Token::Arreglo))
        {
            variable_decl();
            curr_token = lexer.getNextToken();
            if(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
        }
    }
}
void Parser::variable_decl()
{
    type();
    if(checkTk(Token::ID))
    {
        curr_token = lexer.getNextToken();
        while(checkTk(Token::Coma))
        {
            curr_token = lexer.getNextToken();
            if(checkTk(Token::ID))
                curr_token = lexer.getNextToken();
            else 
                throw "Se esperaba ID pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
        }
        if(checkTk(Token::Eol))
            curr_token = lexer.getNextToken();
    }
}
void Parser::type()
{
    if(checkTk(Token::Entero, Token::Booleano, Token::Caracter))
        curr_token = lexer.getNextToken();
    else if(checkTk(Token::Arreglo))
        array_type();
    else
        throw "Se esperaba Entero | booleano | Caracter | Arreglo pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
void Parser::array_type()
{
    if(checkTk(Token::Arreglo))
    {
        curr_token = lexer.getNextToken();
        if(checkTk(Token::OpenBr))
        {
            curr_token = lexer.getNextToken();
            if(checkTk(Token::intConstant))
            {
                curr_token = lexer.getNextToken();
                if(checkTk(Token::CloseBr))
                {
                    curr_token = lexer.getNextToken();
                    if(checkTk(Token::De))
                    {
                        curr_token = lexer.getNextToken();
                        type();
                    }
                    else
                        throw "Se esperaba De pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
                }
                else
                    throw "Se esperaba ']' pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
            }
            else
                throw "Se esperaba un entero(intConstant) pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
        }
        else
            throw "Se esperaba '[' pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    }
    else
        throw "Se esperaba arreglo pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
void Parser::subprogram_decl()
{
    subprogram_header();
    if(checkTk(Token::Eol))
        curr_token = lexer.getNextToken();
    if(checkTk(Token::Entero, Token::Booleano, Token::Caracter, Token::Arreglo))
        variable_section();
    if(checkTk(Token::Inicio))
    {
        curr_token = lexer.getNextToken();
        if(checkTk(Token::ID, Token::Llamar, Token::Escriba, Token::Lea, Token::Retorne, Token::Si, Token::Mientras, Token::Repita, Token::Para))
        {
            statement();
            if(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
            while(checkTk(Token::ID, Token::Llamar, Token::Escriba, Token::Lea, Token::Retorne, Token::Si, Token::Mientras, Token::Repita, Token::Para))
            {
                statement();
            }
        }
        if(checkTk(Token::Eol))
            curr_token = lexer.getNextToken();
        if(checkTk(Token::Fin))
        {
            curr_token = lexer.getNextToken();
            if(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
        }
        else
            throw "Subprogram_Decl -> Se esperaba Fin pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    }
    else
        throw "Subprogram_Decl -> Se esperaba inicio pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
void Parser::subprogram_header()
{
    if(checkTk(Token::Funcion))
        function_header();
    else if(checkTk(Token::Procedimiento))
        procedure_header();
    else
        throw "Se esperaba Funcion | Procedimiento pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
void Parser::function_header()
{
    if(checkTk(Token::Funcion))
    {
        curr_token = lexer.getNextToken();
        if(checkTk(Token::ID))
        {
            curr_token = lexer.getNextToken();
            if(checkTk(Token::OpenPar))
            {
                curr_token = lexer.getNextToken();
                if(checkTk(Token::Var, Token::Entero, Token::Booleano, Token::Caracter, Token::Arreglo))
                {
                    argument_decl();
                    while(checkTk(Token::Coma))
                    {
                        curr_token = lexer.getNextToken();
                        argument_decl();
                    }
                }
                if(checkTk(Token::ClosePar))
                    curr_token = lexer.getNextToken();
            }
            if(checkTk(Token::Colon))
            {
                curr_token = lexer.getNextToken();
                type();
            }
            else
                throw "Se esperaba ':' pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
        }
    }
}
void Parser::procedure_header()
{
    if(checkTk(Token::Procedimiento))
    {
        curr_token = lexer.getNextToken();
        if(checkTk(Token::ID))
        {
            curr_token = lexer.getNextToken();
            if(checkTk(Token::OpenPar))
            {
                curr_token = lexer.getNextToken();
                if(checkTk(Token::Var, Token::Entero, Token::Booleano, Token::Caracter, Token::Arreglo))
                {
                    argument_decl();
                    while(checkTk(Token::Coma))
                    {
                        curr_token = lexer.getNextToken();
                        argument_decl();
                    }
                }
                if(checkTk(Token::ClosePar))
                    curr_token = lexer.getNextToken();
            }
            while(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
        }
        else
            throw "Procedimiento -> Se esperaba ID pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    }
}
void Parser::argument_decl()
{
    if(checkTk(Token::Var))
    {
        curr_token = lexer.getNextToken();
        type();
        if(checkTk(Token::ID))
            curr_token = lexer.getNextToken();
        else
            throw "Se esperaba ID pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    }
    else if(checkTk(Token::Entero, Token::Booleano, Token::Caracter, Token::Arreglo))
    {
        type();
        if(checkTk(Token::ID))
            curr_token = lexer.getNextToken();
        else
            throw "Se esperaba ID pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    }
    else
        throw "Se esperaba Var o Type pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
void Parser::statement()
{
    if(checkTk(Token::ID))
    {
        lvalue();
        if(checkTk(Token::Op_Assign))
        {
            curr_token = lexer.getNextToken();
            expr();
        }
        else
            throw "Statement:ID -> Se esperaba '<-' pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    }
    else if(checkTk(Token::Llamar))
    {
        curr_token = lexer.getNextToken();
        if(checkTk(Token::ID))
        {
            curr_token = lexer.getNextToken();
            if(checkTk(Token::OpenPar))
            {
                curr_token = lexer.getNextToken();
                if(checkTk(Token::ID, Token::Op_Sub, Token::No, Token::OpenPar, Token::stringConstant, Token::intConstant, Token::Verdadero, Token::Falso))
                {
                    expr();
                    while (checkTk(Token::Coma))
                    {
                        curr_token = lexer.getNextToken();
                        expr();
                    }
                }
                if(checkTk(Token::ClosePar))
                    curr_token = lexer.getNextToken();
                else
                    throw "Se esperaba ')' pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
            }
            else { /*Nothing to do here*/ }
        }
    }
    else if(checkTk(Token::Escriba))
    {
        curr_token = lexer.getNextToken();
        if(checkTk(Token::stringConstant, Token::ID, Token::Op_Sub, Token::No, Token::OpenPar, Token::stringConstant, Token::intConstant, 
                    Token::Verdadero, Token::Falso))
        {
            argument();
            while(checkTk(Token::Coma))
            {
                curr_token = lexer.getNextToken();
                argument();
            }
        }
        else
            throw "Se esperaba minimo un argumento pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    }
    else if(checkTk(Token::Lea))
    {
        curr_token = lexer.getNextToken();
        if(checkTk(Token::ID))
        {
            lvalue();
            while(checkTk(Token::Coma))
            {
                curr_token = lexer.getNextToken();
                lvalue();
            }
        }
        else
            throw "Se esperaba minimo un lvalue(ID) pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    }
    else if(checkTk(Token::Retorne))
    {
        curr_token = lexer.getNextToken();
        if(checkTk(Token::ID, Token::Op_Sub, Token::No, Token::OpenPar, Token::stringConstant, Token::intConstant, Token::Verdadero, Token::Falso))
            expr();
        else { /*Nothing to do here*/ }
    }
    else if(checkTk(Token::Si))
        if_statement();
    else if(checkTk(Token::Mientras))
    {
        curr_token = lexer.getNextToken();
        expr();
        if(checkTk(Token::Eol))
            curr_token = lexer.getNextToken();
        if(checkTk(Token::Haga))
        {
            curr_token = lexer.getNextToken();
            if(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
            while(checkTk(Token::ID, Token::Llamar, Token::Escriba, Token::Lea, Token::Retorne, Token::Si, Token::Mientras, Token::Repita, Token::Para))
            {
                statement();
                if(checkTk(Token::Eol))
                    curr_token = lexer.getNextToken();
            }
            while(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
            if(checkTk(Token::Fin))
            {
                curr_token = lexer.getNextToken();
                if(checkTk(Token::Mientras))
                    curr_token = lexer.getNextToken();
                else 
                    throw "Se esperaba Mientras pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
            }
            else 
                throw "Statement Mientras -> Se esperaba Fin pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
        }
        else 
            throw "Se esperaba Haga pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    }
    else if(checkTk(Token::Repita))
    {
        curr_token = lexer.getNextToken();
        if(checkTk(Token::Eol))
            curr_token = lexer.getNextToken();
        while(checkTk(Token::ID, Token::Llamar, Token::Escriba, Token::Lea, Token::Retorne, Token::Si, Token::Mientras, Token::Repita, Token::Para))
        {
            statement();
            if(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
        }
        while(checkTk(Token::Eol))
            curr_token = lexer.getNextToken();
        if(checkTk(Token::Hasta))
        {
            curr_token = lexer.getNextToken();
            expr();
        }
            
        else
            throw "Se esperaba Hasta pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    }
    else if(checkTk(Token::Para))
    {
        curr_token = lexer.getNextToken();
        lvalue();
        if(checkTk(Token::Op_Assign))
        {
            curr_token = lexer.getNextToken();
            expr();
            if(checkTk(Token::Hasta))
            {
                curr_token = lexer.getNextToken();
                expr();
                if(checkTk(Token::Haga))
                {
                    curr_token = lexer.getNextToken();
                    if(checkTk(Token::Eol))
                        curr_token = lexer.getNextToken();
                    while(checkTk(Token::ID, Token::Llamar, Token::Escriba, Token::Lea, Token::Retorne, Token::Si, Token::Mientras, Token::Repita, Token::Para))
                    {
                        statement();
                        if(checkTk(Token::Eol))
                            curr_token = lexer.getNextToken();
                    }
                    while(checkTk(Token::Eol))
                        curr_token = lexer.getNextToken();
                    if(checkTk(Token::Fin))
                    {
                        curr_token = lexer.getNextToken();
                        if(checkTk(Token::Para))
                            curr_token = lexer.getNextToken();
                        else
                            throw "Se esperaba Para pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
                    }
                    else
                        throw " Statement Para -> Se esperaba Fin pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
                }
                else
                    throw "Se esperaba Haga pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
            }
            else
                throw "Se esperaba Hasta pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
        }
        else
            throw "Statement:Para -> Se esperaba '<-' pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    }
    else
        throw "Se esperaba ID | llamar | escriba | lea | retorne | si | mientras | repita | para pero se encontro " + lexer.getText() + 
                " en la linea " + std::to_string(lexer.getLine());
}
void Parser::if_statement()
{

}
void Parser::else_if_block()
{
    if(checkTk(Token::Sino))
    {
        curr_token = lexer.getNextToken();
        if(checkTk(Token::Si))
        {
            curr_token = lexer.getNextToken();
            expr();
            if(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
            if(checkTk(Token::Entonces))
            {
                curr_token = lexer.getNextToken();
                statement();
                if(checkTk(Token::Eol))
                    curr_token = lexer.getNextToken();
                while(checkTk(Token::ID, Token::Llamar, Token::Escriba, Token::Lea, Token::Retorne, Token::Si, Token::Mientras, Token::Repita, Token::Para))
                {
                    statement();
                    if(checkTk(Token::Eol))
                        curr_token = lexer.getNextToken();
                }
                while(checkTk(Token::Eol))
                    curr_token = lexer.getNextToken();
            }
            else
                throw "Se esperaba 'entonces' pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
        }
        else
                throw "Se esperaba 'si' pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    }
}
void Parser::else_block()
{
    if(checkTk(Token::Sino))
    {
        curr_token = lexer.getNextToken();
        if(checkTk(Token::Eol))
            curr_token = lexer.getNextToken();
        statement();
        if(checkTk(Token::Eol))
            curr_token = lexer.getNextToken();
        while(checkTk(Token::ID, Token::Llamar, Token::Escriba, Token::Lea, Token::Retorne, Token::Si, Token::Mientras, Token::Repita, Token::Para))
        {
            statement();
            if(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
        }
    }
}
void Parser::argument()
{
    if(checkTk(Token::stringConstant))
        curr_token = lexer.getNextToken();
    else
        expr();
}
void Parser::lvalue()
{
    if(checkTk(Token::ID))
    {
        curr_token = lexer.getNextToken();
        lvalue_p();
    }
}
void Parser::lvalue_p()
{
    if(checkTk(Token::OpenBr))
    {
        curr_token = lexer.getNextToken();
        expr();
        if(checkTk(Token::CloseBr))
            curr_token = lexer.getNextToken();
        else
            throw "Se esperaba ']' al final de la expr pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    }
    else { /* EPSILON */ }
}
void Parser::expr()
{
    if(checkTk(Token::ID))
    {
        curr_token = lexer.getNextToken();
        if(checkTk(Token::OpenPar))
        {
            expr_p2();
            expr_p();
        }
        else
        {
            lvalue_p();
            expr_p();
        }
    }
    else if(checkTk(Token::intConstant, Token::charConstant, Token::Verdadero,  Token::Falso))
    {
        constant();
        expr_p();
    }
        
    else if(checkTk(Token::Op_Sub))
    {
        curr_token = lexer.getNextToken();
        expr();
        expr_p();
    }
    else if(checkTk(Token::No))
    {
        curr_token = lexer.getNextToken();
        expr();
        expr_p();
    }
    else if(checkTk(Token::OpenPar))
    {
        curr_token = lexer.getNextToken();
        expr();
        if(checkTk(Token::ClosePar))
        {
            curr_token = lexer.getNextToken();
            expr_p();
        }
        else
            throw "Se esperaba ')' al final de la expr pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    }
    else
        throw "Se esperaba ID | const | - | no | ( pero se encontro  " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
void Parser::expr_p()
{
    if(checkTk(Token::Op_Add, Token::Op_Sub, Token::Op_Mul, Token::Op_Pow, Token::Div, Token::Mod, Token::Op_GT, 
        Token::Op_LT, Token::Op_Gre_OE, Token::Op_Less_OE, Token::Op_Equal, Token::Op_Equal_2, Token::Y, Token::O))
    {
        bin_op();
        expr();
    }
    else {/* EPSILON */}
}
void Parser::expr_p2()
{
    if(checkTk(Token::OpenPar))
    {
        curr_token = lexer.getNextToken();
        expr();
        while (checkTk(Token::Coma))
        {
            curr_token = lexer.getNextToken();
            expr();
        }
        if(checkTk(Token::ClosePar))
            curr_token = lexer.getNextToken();
        else
            throw "Se esperaba '(' al final de la expr Pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    }
}
void Parser::bin_op()
{
    if(checkTk(Token::Op_Add, Token::Op_Sub, Token::Op_Mul, Token::Op_Pow, Token::Div, Token::Mod))
        arith_op();
    else if(checkTk(Token::Op_GT, Token::Op_LT, Token::Op_Gre_OE, Token::Op_Less_OE))
        rel_op();
    else if(checkTk(Token::Op_Equal, Token::Op_Equal_2))
        eq_op();
    else if(checkTk(Token::Y, Token::O))
        cond_op();
    else
        throw "Se esperaba operacion arith | rel | eq | cond Pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    
}
void Parser::arith_op()
{
    if(checkTk(Token::Op_Add, Token::Op_Sub, Token::Op_Mul, Token::Op_Pow, Token::Div, Token::Mod))
        curr_token = lexer.getNextToken();
    else
        throw "Se esperaba + | - | * | ^ | Div | Mod Pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
void Parser::rel_op()
{
    if(checkTk(Token::Op_GT, Token::Op_LT, Token::Op_Gre_OE, Token::Op_Less_OE))
        curr_token = lexer.getNextToken();
    else
        throw "Se esperaba < | > | <= | >= Pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
void Parser::eq_op()
{
    if(checkTk(Token::Op_Equal, Token::Op_Equal_2))
        curr_token == lexer.getNextToken();
    else
        throw "Se esperaba = | <> Pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
void Parser::cond_op()
{
    if(checkTk(Token::Y, Token::O))
        curr_token = lexer.getNextToken();
    else
        throw "Se esperaba Y | O Pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
void Parser::constant()
{
    if(checkTk(Token::intConstant, Token::charConstant))
        curr_token = lexer.getNextToken();
    else if(Token::Verdadero, Token::Falso)
        bool_constant();
    else
        throw "Se esperaba : intConstant | charConstant | boolConstant Pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
void Parser::bool_constant()
{
    if(checkTk(Token::Verdadero, Token::Falso))
        curr_token = lexer.getNextToken();
    else
        throw "Se esperaba : Verdadero | Falso Pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}