#include "gen.h"

#include <type_traits>
#include <algorithm>

typedef struct {
  std::map<std::string, std::string> strings;
  std::map<std::string, std::string> identifiers;
  std::map<std::string, std::vector<std::string>> lists;
} Args;

Args get_args(std::vector<std::unique_ptr<scud::ast::ParameterExpr>>& exprs) {
  Args args;
  for (int i = 0; i < exprs.size(); ++i) {
      auto &a = exprs[i];
      auto val = a.get();
      std::string index = val->named ? static_cast<scud::ast::IdentifierExpr*>(val->name.release())->name : std::to_string(i);
      switch (val->value.get()->kind)
      {
      case scud::ast::ExprKind::String:
        {
          auto b = static_cast<scud::ast::StringExpr* >(val->value.release());
          args.strings[index] = b->val;
        }
        break;

      case scud::ast::ExprKind::List:
        {
          auto b = static_cast<scud::ast::ListExpr* >(val->value.release());
          std::vector<std::string> listvals;
          // std::transform(b->values.cbegin(), b->values.cend(), std::back_inserter(listvals), [](const std::unique_ptr<scud::ast::Expr>& ptr){
          //   return *(ptr.get());
          // });

          // for (auto& ptr : b->values) {
          //   auto item = ptr.get();
          //   listvals.push_back(*(ptr.get()));
          // }
        }
        break;
      
      case scud::ast::ExprKind::Identifier:
        {
          auto b = static_cast<scud::ast::IdentifierExpr* >(val->value.release());
        }
        break;
      
      default:
        break;
      }
  }
}

namespace scud {
  void ProgramVisitor::visit(ast::AST& ast) {
    for (auto expr : ast.expressions()) {
      expr.accept(*this);
    }
  }

  void ProgramVisitor::visit_expr(ast::Expr& expr) {};
  void ProgramVisitor::visit_list_expr(ast::ListExpr& expr) {};
  void ProgramVisitor::visit_identifier_expr(ast::IdentifierExpr& expr) {};
  void ProgramVisitor::visit_variable_expr(ast::VariableExpr& expr) {};
  void ProgramVisitor::visit_parameter_expr(ast::ParameterExpr& expr) {};

  void ProgramVisitor::visit_string_expr(ast::StringExpr& expr) {}

  void ProgramVisitor::visit_function_expr(ast::FunctionExpr& expr) {
    std::string name = expr.name;
    Args args = get_args(expr.arguments);
    // in future cases, functions and others will be implemented
    if (name == "project") {
      
    } else if (name == "executable") {

    } else if (name == "library") {

    }
    
  }
}

