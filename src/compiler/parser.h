#ifndef SCUD_PARSER_H
#define SCUD_PARSER_H

#include <string>
#include <vector>
#include <memory>

#include <cstdio>

#include "src/compiler/lexer.h"

namespace scud {

class Visitor;

namespace ast {

// base expression class
class Expr {
public:
    virtual ~Expr() = default;
    virtual void accept(Visitor& visitor);
};

// stringExpr : "string"
class StringExpr: public Expr {
    std::string val;

public:
    StringExpr(std::string val): val(val) {}

    void accept(Visitor& visitor);
};

// listExpr : "[" + [...expression] + "]"
class ListExpr: public Expr {
    std::vector<std::unique_ptr<Expr>> values;

public:
    ListExpr(std::vector<std::unique_ptr<Expr>>& values): values(std::move(values)) {}
    void accept(Visitor& visitor);
};

// identifier expression
class IdentifierExpr: public Expr {
    std::string name;

public:
    IdentifierExpr(std::string name): name(name) {}
    void accept(Visitor& visitor);
};

// variableExpr : identifier + "=" + expression              
class VariableExpr: public Expr {
    std::string name;
    std::unique_ptr<Expr> value;

public:
    VariableExpr(std::string name, std::unique_ptr<Expr>& value): name(name), value(std::move(value)) {}
    void accept(Visitor& visitor);
};

// parameterExpr : expression | namedParameterExpr
//
// namedParameterExpr : identifier + ":" + expression
class ParameterExpr: public Expr {
    bool named;
    std::unique_ptr<Expr> name;
    std::unique_ptr<Expr> value;

public:
    ParameterExpr(std::unique_ptr<Expr>& value, std::unique_ptr<Expr>& _name):
        value(std::move(value)), named(true), name(std::move(_name)) {}
    ParameterExpr(std::unique_ptr<Expr>& value):
        value(std::move(value)), named(false), name(nullptr) {}

    void accept(Visitor& visitor);
};

// functionExpr : identifier + [...parameterExpr] + [body]
class FunctionExpr: public Expr {
    std::string name;
    std::vector<std::unique_ptr<ParameterExpr>> arguments;

public:
    FunctionExpr(std::string name, std::vector<std::unique_ptr<ParameterExpr>>& arguments) :
        name(name), arguments(std::move(arguments)) {}
    
    void accept(Visitor& visitor);
};

// a full AST of a scud file
class AST {
    std::vector<std::unique_ptr<Expr>> _expressions;

public:
    AST(std::vector<std::unique_ptr<Expr>>& expr): _expressions(std::move(expr)) {}

    std::vector<Expr> expressions() const;
};

};

// A Representation class for a Parser
class Parser {
    // The current token being parsed
    int ptr = 0;

public:
    // the total number of tokens present
    std::vector<Token> tokens;

    Parser(std::vector<Token> tokens): tokens(tokens), ptr(0) {}

private:
    // Get the next token
    Token next();

    // get the current token
    Token current();

    // error logger for the parser
    std::unique_ptr<ast::Expr> log_error(const char *str);

    // stringexpr ::= string
    std::unique_ptr<ast::Expr> parse_string_expr();

    // parenexpr ::= '(' expression ')'
    std::unique_ptr<ast::Expr> parse_paren_expr();

    // listexpr ::= '[' expression* ']'
    std::unique_ptr<ast::Expr> parse_list_expr();

    // identifierexpr ::= identifier
    //                ::= identifier '(' expression* ')'
    std::unique_ptr<ast::Expr> parse_identifier_expr();

    // paramexpr ::= '(' expression ')'
    std::unique_ptr<ast::Expr> parse_param_expr();

    // expression
    std::unique_ptr<ast::Expr> parse_expr();

public:
    // used for parsing the tokens and generating an abstract syntax tree (`ast::AST`) from it
    ast::AST parse();
};

// a base visitor class in order to visit and manipulate the AST
class Visitor {
public:
  virtual void visit(ast::AST& ast) = 0;
  virtual void visit_expr(ast::Expr& expr) = 0;
  virtual void visit_string_expr(ast::StringExpr& expr) = 0;
  virtual void visit_list_expr(ast::ListExpr& expr) = 0;
  virtual void visit_identifier_expr(ast::IdentifierExpr& expr) = 0;
  virtual void visit_variable_expr(ast::VariableExpr& expr) = 0;
  virtual void visit_parameter_expr(ast::ParameterExpr& expr) = 0;
  virtual void visit_function_expr(ast::FunctionExpr& expr) = 0;
};

}

#endif