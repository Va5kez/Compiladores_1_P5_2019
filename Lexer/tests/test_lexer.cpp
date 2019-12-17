#include <sstream>
#include <memory>
#include <cstring>
#include "expr_parser.h"
#include "../AST/expr_ast.h"
#include <exception>

std::string toString(Token tk) {
    switch (tk) {
        case Token::Eol: return "EOL";
        case Token::intConstant: return "intConstant";
        case Token::charConstant: return "charConstant";
        case Token::stringConstant: return "stringConstant";
        case Token::ID: return "ID";
        case Token::Op_Add: return "Add";
        case Token::Op_Sub: return "Sub";
        case Token::Op_Mul: return "Mult";
        case Token::Op_Pow: return "Power";
        case Token::Op_Assign: return "Assign";
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
        case Token::Entero: return "Entero"; case Token::Real: return "Real"; case Token::Cadena: return "Cadena";
        case Token::Booleano: return "Booleano"; case Token::Caracter: return "Caracter"; case Token::Arreglo: return "Arreglo";
        case Token::De: return "De"; case Token::Funcion: return "Funcion"; case Token::Procedimiento: return "Procedimiento";
        case Token::Var: return "Var"; case Token::Inicio: return "Inicio"; case Token::Fin: return "Fin";
        case Token::Si: return "Si"; case Token::Entonces: return "Entonces"; case Token::Sino: return "Sino";
        case Token::Para: return "Para"; case Token::Mientras: return "Mientras"; case Token::Haga: return "Haga";
        case Token::Llamar: return "Llamar"; case Token::Repita: return "Repita"; case Token::Hasta: return "Hasta";
        case Token::Caso: return "Caso"; case Token::O: return "O"; case Token::Y: return "Y";
        case Token::No: return "No"; case Token::Div: return "Div"; case Token::Mod: return "Mod";
        case Token::Lea: return "Lea"; case Token::Escriba: return "Escriba"; case Token::Retorne: return "Retorne";
        case Token::Tipo: return "Tipo"; case Token::Es: return "Es"; case Token::Registro: return "Registro";
        case Token::Archivo: return "Archivo"; case Token::Secuencial: return "Secuencial"; case Token::Abrir: return "Abrir";
        case Token::Como: return "Como"; case Token::Lectura: return "Lectura"; case Token::Escritura: return "Escritura";
        case Token::Cerrar: return "Cerrar"; case Token::Leer: return "Leer"; case Token::Escribir: return "Escribir";
        case Token::Verdadero: return "Verdadero"; case Token::Falso: return "Falso"; case Token::Final: return "Final";

        case Token::Eof: return "Eof";
        default: return "Unknown";
    }
}

int main(int argc, char **argv)
{
    std::ifstream file(argv[1]);
    if(file.is_open())
    {
        ExprLexer l(file);
        Parser parser(l);
        bool success = false;
        try
        {
            AST *p = parser.parse();
            std::cout << "Pase del parser " << '\n';
            std::cout << p->toString() << std::endl;
            success = true;
        }
        catch(const char* msg)
        {
            std::cerr << "Error: " << msg << '\n';
            success = false;
        }
        catch(...)
        {
            std::cout << "Ultima token :" << l.getText() << " Linea: " << l.getLine() << " # de token " << toString(parser.getToken()) << '\n';
            std::cerr << "Unknown Exception" << '\n';
        }
        if(success)
            std::cout << "Parser sin errores" << '\n';
        
        /*Token token = l.getNextToken();

        while(token != Token::Eof)
        {
            std::cout << "Token " << toString(token) << " -> " << l.getText() << std::endl;
            token = l.getNextToken();
        }*/
    }
    else
    {
        std::cout << "Error al intentar abrir el archivo" << std::endl;
    }
}