#ifndef _PUBLIC_ENUMS_AST_H_
#define _PUBLIC_ENUMS_AST_H_

enum class ASTNodeKind
{
    // Constants
    ident,
    intConstant,
    charConstant,
    stringConstant,
    verdadero,
    falso,
    // Conditional etc ..
    funcion,
    procedimiento,
    si_stmt,
    sino_si_stmt,
    sino_stmt,
    para_stmt,
    mientras_stmt,
    repita_stmt,
    lea_stmt,
    llamar_stmt,
    escriba_stmt,
    retorne_stmt,
    params_t,
    // Binary Operations
    Op_Arit_Add_Expr,
    Op_Arit_Sub_Expr,
    Op_Arit_Mult_Expr,
    Op_Arit_Pow_Expr,
    Op_Arit_Div_Expr,
    Op_Arit_Mod_Expr,
    Op_Rel_GT_Expr,
    Op_Rel_GTE_Expr,
    Op_Rel_LT_Expr,
    Op_Rel_LTE_Expr,
    Op_Con_Y_Expr,
    Op_Con_O_Expr,
    Op_Equality, // <> == 
    Op_Asignar,
    // Decl
    Decl_subtype,
    Decl_variable,
    Decl_Argument,
    Decl_Subprogram
};

enum class Types{
    Arreglo,
    Booleano,
    Caracter,
    Cadena,
    Entero,
    Real
};

#endif // _PUBLIC_ENUMS_AST_H_