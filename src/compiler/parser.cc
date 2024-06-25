#include "parser.h"

#include <cstdio>
#include <memory>
#include <string>
#include <vector>

#include "lexer.h"

namespace scud {

namespace ast {
void Expr::accept(Visitor& visitor) { return visitor.visit_expr(*this); }

void StringExpr::accept(Visitor& visitor) {
  return visitor.visit_string_expr(*this);
}
void ListExpr::accept(Visitor& visitor) {
  return visitor.visit_list_expr(*this);
}
void IdentifierExpr::accept(Visitor& visitor) {
  return visitor.visit_identifier_expr(*this);
}
void VariableExpr::accept(Visitor& visitor) {
  return visitor.visit_variable_expr(*this);
}
void ParameterExpr::accept(Visitor& visitor) {
  return visitor.visit_parameter_expr(*this);
}
void FunctionExpr::accept(Visitor& visitor) {
  return visitor.visit_function_expr(*this);
}

std::vector<Expr> AST::expressions() const {
  std::vector<Expr> expressions;
  for (auto& a : _expressions) expressions.push_back(*a.get());
  return expressions;
}
};  // namespace ast

// Get the next token
Token Parser::next() { return tokens[++ptr]; }

Token Parser::current() { return tokens[ptr]; }

std::unique_ptr<ast::Expr> Parser::log_error(const char* str) {
  fprintf(stderr, "Error: %s\n", str);
  return nullptr;
}

// stringexpr ::= string
std::unique_ptr<ast::Expr> Parser::parse_string_expr() {
  auto result = std::make_unique<ast::StringExpr>(current().lexeme);
  next();
  return std::move(result);
}

// parenexpr ::= '(' expression ')'
std::unique_ptr<ast::Expr> Parser::parse_paren_expr() {
  next();  // eat '('
  auto V = parse_expr();
  if (!V) return nullptr;

  if (current().kind != Token::TokenKind::right_paren)
    return log_error("expected ')'");
  next();  // eat ).
  return V;
}

// listexpr ::= '[' expression* ']'
std::unique_ptr<ast::Expr> Parser::parse_list_expr() {
  next();  // eat '['
  std::vector<std::unique_ptr<ast::Expr>> expressions{};
  while (current().kind != Token::TokenKind::right_square_paren) {
    if (current().kind == Token::TokenKind::eof)
      log_error("Expected ']', got to end of file");

    auto v = parse_expr();
    if (!v) expressions.push_back(nullptr);

    if (current().kind == Token::TokenKind::right_square_paren) {
      break;
    }

    if (current().kind != Token::TokenKind::comma) {
      log_error(
          ("Expected ',' in list, but got " + current().to_string()).c_str());
    } else {
      next();  // eat ','
    }
  }
  next();  // eat ']'
  return std::make_unique<ast::ListExpr>(expressions);
}

// identifierexpr ::= identifier
//                ::= identifier '(' expression* ')'
std::unique_ptr<ast::Expr> Parser::parse_identifier_expr() {
  std::string id_name = current().lexeme;
  next();

  if (current().kind != Token::TokenKind::left_paren) {
    return std::make_unique<ast::IdentifierExpr>(id_name);
  }

  std::vector<std::unique_ptr<ast::ParameterExpr>> args{};
  if (current().kind != Token::TokenKind::right_paren) {
    next();  // eat '('
    while (true) {
      auto arg = parse_param_expr();
      if (arg != nullptr)
        args.push_back(std::move(std::unique_ptr<ast::ParameterExpr>(
            static_cast<ast::ParameterExpr*>(arg.release()))));
      else
        return nullptr;

      if (current().kind == Token::TokenKind::right_paren) {
        next();  // eat ')'
        break;
      }
      if (current().kind == Token::TokenKind::eof) {
        return log_error("Expected ')', got eof");
      }
      if (current().kind != Token::TokenKind::comma)
        return log_error("Expected ')' or ',' in argument call for function.");
      next();
    }
  }
  return std::make_unique<ast::FunctionExpr>(id_name, args);
}

std::unique_ptr<ast::Expr> Parser::parse_param_expr() {
  Token curr = current();
  auto v = parse_expr();
  if (current().kind == Token::TokenKind::colon) {
    if (curr.kind != Token::TokenKind::identifier)
      return log_error("Expected identifier before colon in named parameter");
    next();  // eat ':'

    if (auto value = parse_expr()) {
      return std::make_unique<ast::ParameterExpr>(value, v);
    } else {
      return nullptr;
    }
  } else {
    if (v != nullptr) {
      return std::make_unique<ast::ParameterExpr>(v);
    } else {
      return nullptr;
    }
  }
}

std::unique_ptr<ast::Expr> Parser::parse_expr() {
  switch (current().kind) {
    case Token::TokenKind::identifier:
      return parse_identifier_expr();
      break;
    case Token::TokenKind::string:
      return parse_string_expr();
    case Token::TokenKind::left_square_paren:
      return parse_list_expr();
    case Token::TokenKind::left_paren:
      return parse_paren_expr();
    default:
      return log_error(
          ("unknown token when parsing expression: " + current().to_string())
              .c_str());
      break;
  }
}

ast::AST Parser::parse() {
  std::vector<std::unique_ptr<ast::Expr>> expressions;
  bool loop = true;
  while (loop) {
    switch (current().kind) {
      case Token::TokenKind::eof:
        loop = false;
        break;
      default:
        auto expr = parse_expr();
        if (expr != nullptr)
          expressions.push_back(std::move(expr));
        else
          exit(0);
        break;
    }
  }
  return ast::AST(expressions);
}

}  // namespace scud
