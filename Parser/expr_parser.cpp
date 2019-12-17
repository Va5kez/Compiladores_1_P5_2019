#include "expr_parser.h"

AST *Parser::parse()
{
    curr_token = lexer.getNextToken();
    AST *p = program();
    while(checkTk(Token::Eol))
        curr_token = lexer.getNextToken();
    if(checkTk(Token::Eof))
        std::cout << "Se llego al final del archivo" << '\n';
    else
    {
        std::cout << lexer.getText() << '\n';
        throw "Error en el parser: Sobraron tokens ";
    }
    return p;
}
AST *Parser::program()
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
            if(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
        }
        if(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
    }
    if(checkTk(Token::Inicio))
    {
        std::list<AST *> stmtlist;
        curr_token = lexer.getNextToken();
        while(checkTk(Token::Eol))
            curr_token = lexer.getNextToken();
        if(checkTk(Token::ID, Token::Llamar, Token::Escriba, Token::Lea, Token::Retorne, Token::Si, Token::Mientras, Token::Repita, Token::Para))
        {
            //AST *temp = statement();
            stmtlist.push_back(statement());
            while(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
            while(checkTk(Token::ID, Token::Llamar, Token::Escriba, Token::Lea, Token::Retorne, Token::Si, Token::Mientras, Token::Repita, Token::Para))
            {
                //temp2 = statement();
                stmtlist.push_back(statement());
                while(checkTk(Token::Eol))
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
            StatementList *e = new StatementList(stmtlist);
            //std::cout << e->toString() << std::endl;
            return e;
        }
        else
            throw "Program -> Se esperaba Fin pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    }
    else
        throw "Program -> Se esperaba Inicio pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
AST *Parser::subtypes_sections()
{
    if(checkTk(Token::Tipo))
    {
        subtype_decl();
        if(checkTk(Token::Eol))
            curr_token = lexer.getNextToken();
        while(checkTk(Token::Tipo))
        {
            subtype_decl();
            if(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
        }
    }
    throw "Subtypes_sections -> Se esperaba Tipo pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
AST *Parser::subtype_decl()
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
AST *Parser::variable_section()
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
AST *Parser::variable_decl()
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
Types Parser::type()
{
    if(checkTk(Token::Entero, Token::Booleano, Token::Caracter))
        curr_token = lexer.getNextToken();
    else if(checkTk(Token::Arreglo))
        array_type();
    else
        throw "Se esperaba Entero | booleano | Caracter | Arreglo pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
Types Parser::array_type()
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
AST *Parser::subprogram_decl()
{
    subprogram_header();
    if(checkTk(Token::Eol))
        curr_token = lexer.getNextToken();
    if(checkTk(Token::Entero, Token::Booleano, Token::Caracter, Token::Arreglo))
        variable_section();
    if(checkTk(Token::Inicio))
    {
        curr_token = lexer.getNextToken();
        if(checkTk(Token::Eol))
            curr_token = lexer.getNextToken();
        if(checkTk(Token::ID, Token::Llamar, Token::Escriba, Token::Lea, Token::Retorne, Token::Si, Token::Mientras, Token::Repita, Token::Para))
        {
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
AST *Parser::subprogram_header()
{
    if(checkTk(Token::Funcion))
        function_header();
    else if(checkTk(Token::Procedimiento))
        procedure_header();
    else
        throw "Se esperaba Funcion | Procedimiento pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
AST *Parser::function_header()
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
AST *Parser::procedure_header()
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
AST *Parser::argument_decl()
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
AST *Parser::statement()
{
    if(checkTk(Token::ID))
    {
        AST *temp;
        std::string l = lvalue();
        if(checkTk(Token::Op_Assign))
        {
            curr_token = lexer.getNextToken();
            temp = expr();
            AsignarExpr *f =  new AsignarExpr(l, temp);
            return f;
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
        AST *temp;
        curr_token = lexer.getNextToken();
        if(checkTk(Token::stringConstant, Token::ID, Token::Op_Sub, Token::No, Token::OpenPar, Token::charConstant, Token::intConstant, 
                    Token::Verdadero, Token::Falso))
        {
            temp = argument();
            while(checkTk(Token::Coma))
            {
                curr_token = lexer.getNextToken();
                argument();
                if(checkTk(Token::Eol))
                    curr_token = lexer.getNextToken();
            }
            if(checkTk(Token::Eol))
                    curr_token = lexer.getNextToken();
            EscribaStatement *s = new EscribaStatement(temp);
            return s;
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
        std::list<AST *> rp_stmtlist;
        curr_token = lexer.getNextToken();
        if(checkTk(Token::Eol))
            curr_token = lexer.getNextToken();
        while(checkTk(Token::ID, Token::Llamar, Token::Escriba, Token::Lea, Token::Retorne, Token::Si, Token::Mientras, Token::Repita, Token::Para))
        {
            rp_stmtlist.push_back(statement());
            if(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
        }
        while(checkTk(Token::Eol))
            curr_token = lexer.getNextToken();
        if(checkTk(Token::Hasta))
        {
            curr_token = lexer.getNextToken();
            AST *tem = expr();
            RepitaStatement *f = new RepitaStatement(tem, rp_stmtlist);
            return f;
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
AST *Parser::if_statement()
{
    if(checkTk(Token::Si))
    {
        curr_token = lexer.getNextToken();
        expr();
        while(checkTk(Token::Eol))
            curr_token = lexer.getNextToken();
        if(checkTk(Token::Entonces))
        {
            curr_token = lexer.getNextToken();
            while(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
            statement();
            while(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
            while(checkTk(Token::ID, Token::Llamar, Token::Escriba, Token::Lea, Token::Retorne, Token::Si, Token::Mientras, Token::Repita, Token::Para))
            {
                statement();
                while(checkTk(Token::Eol))
                    curr_token = lexer.getNextToken();
            }
            if(checkTk(Token::Sino))
            {
                curr_token = lexer.getNextToken();
                if(checkTk(Token::Si))
                {
                    else_if_block();
                    while(checkTk(Token::Eol))
                        curr_token = lexer.getNextToken();
                    while(checkTk(Token::Sino))
                    {
                        curr_token = lexer.getNextToken();
                        if(checkTk(Token::Si))
                        {
                            else_if_block();
                            while(checkTk(Token::Eol))
                                curr_token = lexer.getNextToken();
                        }
                        else
                        {
                            else_block();
                            while(checkTk(Token::Eol))
                                curr_token = lexer.getNextToken();
                            break;
                        }
                    }   
                }
                else
                {
                    else_block();
                    while(checkTk(Token::Eol))
                        curr_token = lexer.getNextToken();
                } 
            }
            if(checkTk(Token::Fin))
            {
                curr_token = lexer.getNextToken();
                if(checkTk(Token::Si))
                {
                    curr_token = lexer.getNextToken();
                    while(checkTk(Token::Eol))
                        curr_token = lexer.getNextToken();

                }
                else
                    throw "Falto Si al final del Fin " + '\n';
            }
        }
        else
            throw "If-statement -> Se esperaba Entonces pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    }
    else
        throw "If_statement -> Se esperaba Si pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
AST *Parser::else_if_block()
{
    if(checkTk(Token::Si))
    {
        curr_token = lexer.getNextToken();
        expr();
        while(checkTk(Token::Eol))
            curr_token = lexer.getNextToken();
        if(checkTk(Token::Entonces))
        {
            curr_token = lexer.getNextToken();
            while(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
            statement();
            while(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
            while(checkTk(Token::ID, Token::Llamar, Token::Escriba, Token::Lea, Token::Retorne, Token::Si, Token::Mientras, Token::Repita, Token::Para))
            {
                statement();
                while(checkTk(Token::Eol))
                    curr_token = lexer.getNextToken();
            }
            while(checkTk(Token::Eol))
                curr_token = lexer.getNextToken();
        }
        else
            throw "Se esperaba Entonces pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    }
    else
        throw "Se esperaba 'si' pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
AST *Parser::else_block()
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
AST *Parser::argument()
{
    if(checkTk(Token::stringConstant))
    {
        std::string l = lexer.getText();
        curr_token = lexer.getNextToken();
        StringConstantExpr *temp = new StringConstantExpr(l);
        return temp;
    }
    else
        return expr();
}
std::string Parser::lvalue()
{
    if(checkTk(Token::ID))
    {
        std::string l = lexer.getText();
        curr_token = lexer.getNextToken();
        if(checkTk(Token::OpenBr))
        {
            AST *a = lvalue_p();
            LvalueExpr *f = new LvalueExpr(l,a);
            return f->toString();
        }
        return l;
    }
}
AST *Parser::lvalue_p()
{
    if(checkTk(Token::OpenBr))
    {
        curr_token = lexer.getNextToken();
        AST *t = expr();
        if(checkTk(Token::CloseBr))
        {
            curr_token = lexer.getNextToken();
            return t;
        }
            
        else
            throw "Se esperaba ']' al final de la expr pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    }
    else { /* EPSILON */ }
}
AST *Parser::expr()
{
    if(checkTk(Token::ID))
    {
        std::string t = lexer.getText();
        IdentExpr *l = new IdentExpr(lexer.getText(), "0");
        curr_token = lexer.getNextToken();
        if(checkTk(Token::OpenPar))
        {
            expr_p2();
            expr_p();
        }
        else
        {
            if(checkTk(Token::OpenBr))
            {
                AST *z = lvalue_p();
                LvalueExpr *j = new LvalueExpr(t,z);
                return j;
            }
            std::string op;
            switch (curr_token)
            {
                case Token::Op_Add: op = "+"; break;
                case Token::Op_Sub: op = "-"; break;
                case Token::Op_Mul: op = "*"; break;
                case Token::Div: op = "div"; break;
                case Token::Op_Pow: op = "^"; break;
                case Token::Mod: op = "mod"; break;
                case Token::Op_GT: op = ">"; break;
                case Token::Op_Gre_OE: op = ">="; break;
                case Token::Op_LT: op = "<"; break;
                case Token::Op_Less_OE: op = "<="; break;
            }
            AST *tem = expr_p();
            if(op == "+") { AddExpr *f = new AddExpr(l, tem); return f; }
            else if(op == "-") { SubExpr *f = new SubExpr(l, tem); return f; }
            else if(op == "*") { MultExpr *f = new MultExpr(l, tem); return f; }
            else if(op == "div") { DivExpr *f = new DivExpr(l, tem); return f; }
            else if(op == "^") { PowExpr *f = new PowExpr(l, tem); return f; }
            else if(op == "mod") { ModExpr *f = new ModExpr(l, tem); return f; }
            else if(op == ">") { GTExpr *f = new GTExpr(l, tem); return f; }
            else if(op == ">=") { GTEExpr *f = new GTEExpr(l, tem); return f; }
            else if(op == "<") { LTExpr *f = new LTExpr(l, tem); return f; }
            else if(op == "<=") { LTEExpr *f = new LTEExpr(l, tem); return f; }
        }
        return l;
    }
    else if(checkTk(Token::intConstant, Token::charConstant, Token::Verdadero,  Token::Falso))
    {
        std::string f = lexer.getText();
        std::string l = constant();
        if(l == "intConstant")
        {
            IntConstantExpr *a = new IntConstantExpr(std::stoi(f));
            return a;
        }
        else if(l == "charConstant")
        {
            CharConstantExpr *a = new CharConstantExpr(f);
            return a;
        }
        else if(l == "verdadero" || l == "falso")
        {
            bool s = l == "falso" ? 0 : 1;
            BooleanConstantExpr *a = new BooleanConstantExpr(s);
            return a;
        }
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
    {
        std::cout << "Me pase" << '\n';
        throw "Se esperaba ID | const | - | no | ( pero se encontro  " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    }
        
}
AST *Parser::expr_p()
{
    if(checkTk(Token::Op_Add, Token::Op_Sub, Token::Op_Mul, Token::Op_Pow, Token::Div, Token::Mod, Token::Op_GT, 
        Token::Op_LT, Token::Op_Gre_OE, Token::Op_Less_OE, Token::Op_Equal, Token::Op_Equal_2, Token::Y, Token::O))
    {
        bin_op();
        return expr();
    }
    else {/* EPSILON */}
}
AST *Parser::expr_p2()
{
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
            if(checkTk(Token::ClosePar))
            {
                curr_token = lexer.getNextToken();
                if(checkTk(Token::Eol))
                    curr_token = lexer.getNextToken();
            }
            else
                throw "Se esperaba '(' al final de la expr Pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
        }
        else
        {
            if(checkTk(Token::ClosePar))
            {
                curr_token = lexer.getNextToken();
                if(checkTk(Token::Eol))
                    curr_token = lexer.getNextToken();
            }
            else
                throw "Se esperaba '(' al final de la expr Pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
        }
    }
    else { /*EPSILON*/ }
}
std::string Parser::bin_op()
{
    if(checkTk(Token::Op_Add, Token::Op_Sub, Token::Op_Mul, Token::Op_Pow, Token::Div, Token::Mod))
        return arith_op();
    else if(checkTk(Token::Op_GT, Token::Op_LT, Token::Op_Gre_OE, Token::Op_Less_OE))
        return rel_op();
    else if(checkTk(Token::Op_Equal, Token::Op_Equal_2))
        return eq_op();
    else if(checkTk(Token::Y, Token::O))
        return cond_op();
    else
        throw "Se esperaba operacion arith | rel | eq | cond Pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
    
}
std::string Parser::arith_op()
{
    if(checkTk(Token::Op_Add, Token::Op_Sub, Token::Op_Mul, Token::Op_Pow, Token::Div, Token::Mod))
    {
        std::string l;
        switch (curr_token)
        {
        case Op_Add:
            l = "+";
            break;
        case Op_Sub:
            l = "-";
            break;
        case Op_Mul:
            l = "*";
            break;
        case Op_Pow:
            l = "^";
            break;
        case Div:
            l = "div";
            break;
        case Mod:
            l = "mod";
            break;
        }
        curr_token = lexer.getNextToken();
        return l;
    }
    else
        throw "Se esperaba + | - | * | ^ | Div | Mod Pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
std::string Parser::rel_op()
{
    if(checkTk(Token::Op_GT, Token::Op_LT, Token::Op_Gre_OE, Token::Op_Less_OE))
    {
        std::string l;
        switch (curr_token)
        {
        case Op_GT:
            l = ">";
            break;
        case Op_Gre_OE:
            l = ">=";
            break;
        case Op_LT:
            l = "<";
            break;
        case Op_Less_OE:
            l = "<=";
            break;
        }
        curr_token = lexer.getNextToken();
        return l;
    }
    else
        throw "Se esperaba < | > | <= | >= Pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
std::string Parser::eq_op()
{
    if(checkTk(Token::Op_Equal, Token::Op_Equal_2))
    {
        std::string l = curr_token == Token::Op_Equal ? "=" : "<>";
        curr_token = lexer.getNextToken();
        return l;
    }
        
    else
        throw "Se esperaba = | <> Pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
std::string Parser::cond_op()
{
    if(checkTk(Token::Y, Token::O))
    {
        std::string l = curr_token == Token::Y ? "y" : "o";
        curr_token = lexer.getNextToken();
        return l;
    }
    else
        throw "Se esperaba Y | O Pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
std::string Parser::constant()
{
    if(checkTk(Token::intConstant, Token::charConstant))
    {
        std::string l = curr_token == Token::intConstant ? "intConstant" : "charConstant";
        curr_token = lexer.getNextToken();
        return l;
    }
        
    else if(Token::Verdadero, Token::Falso)
        return bool_constant();
    else
        throw "Se esperaba : intConstant | charConstant | boolConstant Pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}
std::string Parser::bool_constant()
{
    if(checkTk(Token::Verdadero, Token::Falso))
    {
        std::string l = curr_token == Token::Verdadero ? "verdadero" : "falso";
        curr_token = lexer.getNextToken();
        return l;
    }
        
    else
        throw "Se esperaba : Verdadero | Falso Pero se encontro " + lexer.getText() + " en la linea " + std::to_string(lexer.getLine());
}