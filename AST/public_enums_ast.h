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
    si,
    sino,
    para,
    mientras,
    llamar,
    repita,
    lea,
    escriba,
    retorne,
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
    Op_Equality // <> == 
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