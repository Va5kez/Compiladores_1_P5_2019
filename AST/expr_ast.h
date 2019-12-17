#ifndef _EXPR_AST_H_
#define _EXPR_AST_H_

#include <string>
#include <list>
#include "public_enums_ast.h"

class AST{
    public:
        virtual std::string toString() = 0;
        virtual ASTNodeKind getKind() = 0;
};

class Statement : public AST{
    public:
        Statement() {}
        ~Statement() {}
        virtual ASTNodeKind getKind() = 0;
        virtual std::string toString() = 0;
};
/*
class Program : public Statement{
    public:
        Program() {}
        ~Program() {}
        virtual ASTNodeKind getKind() = 0;
        virtual std::list<Params *> getParams() = 0;
        virtual std::string getName() = 0; 
        virtual std::string toString() = 0;
};

class Params : public Statement{
    public:
        Params(std::string name, Types type) : name(name), type(type) {}
        ~Params() {}
        ASTNodeKind getKind() override { return ASTNodeKind::params_t; }
        std::string toString() = 0;
        std::string name;
        Types type;
};
*/
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
        std::string toString() override { return std::to_string(value); }
        char value; 
};

template <typename T>
class IdentExpr : public AST{
    public:
        IdentExpr(std::string id, T value) : id(id), value(value) {}
        ~IdentExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::ident; }
        std::string getId() {return id; }
        std::string toString() override { return std::to_string(value); }
        std::string id;
        T value;
};

class IntConstantExpr : public AST{
    public:
        IntConstantExpr(int value) : value(value) {}
        ~IntConstantExpr() {}
        ASTNodeKind  getKind() override { return ASTNodeKind::intConstant; }
        std::string toString() override { return std::to_string(value); }
        int value;
};

class StringConstantExpr : public AST{
    public:
        StringConstantExpr(std::string value) : str_val(value) {}
        ~StringConstantExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::stringConstant; }
        std::string toString() override { return str_val; }
        std::string str_val;
};

class AddExpr : public AST{
    public:
        AddExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~AddExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Arit_Add_Expr; }
        std::string toString() override { return lhs->toString()+" + "+rhs->toString();}
        AST *lhs, *rhs;
};

class SubExpr : public AST{
    public:
        SubExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~SubExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Arit_Sub_Expr; }
        std::string toString() override { return lhs->toString()+" - "+rhs->toString(); }
        AST *lhs, *rhs;
};

class MultExpr : public AST{
    public:
        MultExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~MultExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Arit_Mult_Expr; }
        std::string toString() override { return lhs->toString()+" * "+rhs->toString(); }
        AST *lhs, *rhs;
};

class DivExpr : public AST{
    public:
        DivExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~DivExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Arit_Div_Expr; }
        std::string toString() override { return lhs->toString()+" div "+rhs->toString(); }
        AST *lhs, *rhs;
};

class ModExpr : public AST{
    public:
        ModExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~ModExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Arit_Mod_Expr; }
        std::string toString() override { return lhs->toString()+" mod "+rhs->toString(); }
        AST *lhs, *rhs;
};

class PowExpr : public AST{
    public:
        PowExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~PowExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Arit_Pow_Expr; }
        std::string toString() override { return lhs->toString()+" ^ "+rhs->toString(); }
        AST *lhs, *rhs;
};

class GTExpr : public AST{
    public:
        GTExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~GTExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Rel_GT_Expr; }
        std::string toString() override { return lhs->toString()+" < "+rhs->toString(); }
        AST *lhs, *rhs;
};

class GTEExpr : public AST{
    public:
        GTEExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~GTEExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Rel_GTE_Expr; }
        std::string toString() override { return lhs->toString()+" <= "+rhs->toString(); }
        AST *lhs, *rhs;
};

class LTExpr : public AST{
    public:
        LTExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~LTExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Rel_LT_Expr; }
        std::string toString() override { return lhs->toString()+" > "+rhs->toString(); }
        AST *lhs, *rhs;
};

class LTEExpr : public AST{
    public:
        LTEExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~LTEExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Rel_LTE_Expr; }
        std::string toString() override { return lhs->toString()+" >= "+rhs->toString(); }
        AST *lhs, *rhs;
};

class YExpr : public AST{
    public:
        YExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~YExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Con_Y_Expr; }
        std::string toString() override { return lhs->toString()+" y "+rhs->toString(); }
        AST *lhs, *rhs;
};

class OExpr : public AST{
    public:
        OExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~OExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Con_O_Expr; }
        std::string toString() override { return lhs->toString()+" o "+rhs->toString(); }
        AST *lhs, *rhs;
};

class EqualityExpr : public AST{
    public:
        EqualityExpr(AST *x, AST *y) : lhs(x), rhs(y) {}
        ~EqualityExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Equality; }
        std::string toString() override { return lhs->toString()+" = "+rhs->toString(); }
        AST *lhs, *rhs;
};

class AsignarExpr : public AST{
    public:
        AsignarExpr(AST *lvalue, AST *expr) : lvalue(lvalue), expr(expr) {}
        ~AsignarExpr() {}
        ASTNodeKind getKind() override { return ASTNodeKind::Op_Asignar; }
        std::string toString() override { return lvalue->toString()+"<-"+expr->toString(); }
        AST *lvalue, *expr;
};
/*
class SiStatement : public Statement{
    public:
        SiStatement(AST *expr, std::list<Statement *> Stmtlist, std::list<SinoSiStatement *> sinosi_stmtlist, std::list<SinoStatement *> sino_stmtlist) 
                    : expr_if(expr), if_stmtlist(Stmtlist), ss_stmtlist(sinosi_stmtlist), s_stmtlist(sino_stmtlist) {}
        ~SiStatement() {}
        ASTNodeKind getKind() override { return ASTNodeKind::si_stmt; }
        AST *expr_if;
        std::list<Statement *> if_stmtlist;
        std::list<SinoSiStatement *> ss_stmtlist;
        std::list<SinoStatement *> s_stmtlist;
        std::string toString() override { return " "; }
};

class SinoSiStatement : public Statement{
    public:
        SinoSiStatement(AST *expr, std::list<Statement *> Stmtlist) : expr(expr), Sino_si_stmtlist(Stmtlist) {}
        ~SinoSiStatement() {}
        ASTNodeKind getKind() override { return ASTNodeKind::sino_si_stmt; }
        std::string toString() override { return " "; }
        AST *expr;
        std::list<Statement *> Sino_si_stmtlist;
};

class SinoStatement : public Statement{
    public:
        SinoStatement(std::list<Statement *> Stmtlist) : Sino_stmtlist(Stmtlist) {}
        ~SinoStatement() {}
        ASTNodeKind getKind() override { return ASTNodeKind::sino_stmt; }
        std::string toString() override { return " "; }
        std::list<Statement *> Sino_stmtlist;
};

class MientrasStatement : public Statement{
    public:
        MientrasStatement(AST *expr, std::list<Statement *> Stmtlist) : expr(expr), mientras_stmtlist(Stmtlist) {}
        ~MientrasStatement() {}
        ASTNodeKind getKind() override { return ASTNodeKind::mientras_stmt; }
        std::string toString() override { return " "; }
        AST *expr;
        std::list<Statement *> mientras_stmtlist;
};

class RepitaStatement : public Statement{
    public:
        RepitaStatement(AST *expr, std::list<Statement *> Stmtlist) : expr(expr), repita_stmtlist(Stmtlist) {}
        ~RepitaStatement() {}
        ASTNodeKind getKind() override { return ASTNodeKind::repita_stmt; }
        std::string toString() override { return " "; }
        AST *expr;
        std::list<Statement *> repita_stmtlist;
};

class ParaStatement : public Statement{
    public:
        ParaStatement(AsignarExpr *asignar, AST *expr, std::list<Statement *> Stmtlist) : asignar(asignar), expr(expr),
                    para_stmtlist(para_stmtlist) {}
        ~ParaStatement() {}
        ASTNodeKind getKind() override { return ASTNodeKind::para_stmt; }
        std::string toString() override { return " "; }
        AsignarExpr *asignar;
        AST *expr;
        std::list<Statement *> para_stmtlist;
};
*/
class LeaStatement :public Statement {
    public:
        LeaStatement(AST *lvalue) : lvalue_list(lvalue) {} // Needs to be changed
        ~LeaStatement() {}
        ASTNodeKind getKind() override { return ASTNodeKind::lea_stmt; }
        std::string toString() override { return " "; }
        AST *lvalue_list;
};

class LlamarStatement : public Statement{
    public:
        LlamarStatement(std::string id, AST *expr) : id(id), expr(expr) {}
        ~LlamarStatement() {}
        ASTNodeKind getKind() override { return ASTNodeKind::llamar_stmt; }
        std::string toString() override { return " "; }
        std::string id;
        AST *expr;
};

class RetorneStatement : public Statement{
    public:
        RetorneStatement(AST *expr) : expr(expr)  {}
        ~RetorneStatement() {}
        ASTNodeKind getKind() override { return ASTNodeKind::retorne_stmt; }
        std::string toString() override { return " "; }
        AST *expr;
};

class EscribaStatement : public Statement{
    public:
        EscribaStatement(AST *expr) : expr(expr)/*argumentlist(arguments)*/ {} // list arguments.
        ~EscribaStatement() {}
        ASTNodeKind getKind() override { return ASTNodeKind::escriba_stmt; }
        std::string toString() override { return "Escriba "+expr->toString(); }
        AST *expr;
        //std::list<AST *> argumentlist;
};
/*
class Funcion : public Program{
    public:
        Funcion(std::string name, Types type, std::list<Params *> params) : name(name), type(type), params(params)  {}
        ~Funcion() {}
        ASTNodeKind getKind() override { return ASTNodeKind::funcion; }
        std::string getName() override { return name; }
        std::string toString() override { return " "; }
        std::list<Params *>  getParams() override { return params; }
        std::string name;
        Types type;
        std::list<Params *> params;
};

class Procedimiento : public Program{
    public:
        Procedimiento(std::string name, std::list<Params *> params) : name(name), params(params) {}
        ~Procedimiento() {}
        ASTNodeKind getKind() override { return ASTNodeKind::procedimiento; }
        std::string getName() override { return name; }
        std::string toString() override { return " "; }
        std::list<Params *> getParams() override { return params; }
        std::string name;
        std::list<Params *> params;
};
*/
#endif // _EXPR_AST_H_