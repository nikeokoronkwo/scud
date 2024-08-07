#ifndef SCUD_SRC_GEN_GEN_H_
#define SCUD_SRC_GEN_GEN_H_

#include <map>

#include "src/api/project.h"
#include "src/compiler/parser.h"

namespace scud {
class ProgramVisitor : public Visitor {
  api::ScudProject project;
  std::map<std::string, std::string> variables;

 public:
  ProgramVisitor() { project = {}; }

  void visit(ast::AST& ast) override;
  void visit_expr(ast::Expr& expr) override;
  void visit_string_expr(ast::StringExpr& expr) override;
  void visit_list_expr(ast::ListExpr& expr) override;
  void visit_identifier_expr(ast::IdentifierExpr& expr) override;
  void visit_variable_expr(ast::VariableExpr& expr) override;
  void visit_parameter_expr(ast::ParameterExpr& expr) override;
  void visit_function_expr(ast::FunctionExpr& expr) override;
};

}  // namespace scud
#endif