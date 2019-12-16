#ifndef _EXPR_AST_H_
#define _EXPR_AST_H_

#include <string>
#include "public_enums_ast.h"

class AST{
    public:
        virtual ASTNodeKind getKind() = 0;
};

class Statement : public AST{
    public:
        Statement() {}
        ~Statement() {}
        virtual ASTNodeKind getKind() = 0;
};

class BooleanConstantExpr : public AST{
    public:
        BooleanConstantExpr(bool value) : value(value) {}
        ~BooleanConstantExpr() {}
        ASTNodeKind getKind() override { return value == true ? ASTNodeKind::verdadero : ASTNodeKind::falso; }
        bool value;
};

class CharConstantExpr : public AST{
    public:
        CharConstantExpr(char value) : value(value) {}
        ~CharConstantExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::charConstant; }
        char value; 
};

template <typename T>
class IdentExpr : public AST{
    public:
        IdentExpr(std::string id, T value) : id(id), value(value) {}
        ~IdentExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::ident; }
        std::string getId() {return id; }
        std::string id;
        auto value;
};

class IntConstantExpr : public AST{
    public:
        IntConstantExpr(int value) : value(value) {}
        ~IntConstantExpr() {}
        ASTNodeKind  getKind() override { return ASTNodeKind::intConstant; }
        int value;
};

class StringConstantExpr : public AST{
    public:
        StringConstantExpr(std::string value) : str_val(value) {}
        ~StringConstantExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::stringConstant; }
        std::string str_val;
};

class AddExpr : public AST{
    public:
        AddExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~AddExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Arit_Add_Expr; }
        AST *lhs, *rhs;
};

class SubExpr : public AST{
    public:
        SubExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~SubExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Arit_Sub_Expr; }
        AST *lhs, *rhs;
};

class MultExpr : public AST{
    public:
        MultExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~MultExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Arit_Mult_Expr; }
        AST *lhs, *rhs;
};

class DivExpr : public AST{
    public:
        DivExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~DivExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Arit_Div_Expr; }
        AST *lhs, *rhs;
};

class ModExpr : public AST{
    public:
        ModExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~ModExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Arit_Mod_Expr; }
        AST *lhs, *rhs;
};

class PowExpr : public AST{
    public:
        PowExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~PowExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Arit_Pow_Expr; }
        AST *lhs, *rhs;
};

class GTExpr : public AST{
    public:
        GTExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~GTExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Rel_GT_Expr; }
        AST *lhs, *rhs;
};

class GTEExpr : public AST{
    public:
        GTEExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~GTEExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Rel_GTE_Expr; }
        AST *lhs, *rhs;
};

class LTExpr : public AST{
    public:
        LTExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~LTExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Rel_LT_Expr; }
        AST *lhs, *rhs;
};

class LTEExpr : public AST{
    public:
        LTEExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~LTEExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Rel_LTE_Expr; }
        AST *lhs, *rhs;
};

class YExpr : public AST{
    public:
        YExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~YExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Con_Y_Expr; }
        AST *lhs, *rhs;
};

class OExpr : public AST{
    public:
        OExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~OExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Con_O_Expr; }
        AST *lhs, *rhs;
};

class EqualityExpr : public AST{
    public:
        EqualityExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~EqualityExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Equality; }
        AST *lhs, *rhs;
};

#endif // _EXPR_AST_H_