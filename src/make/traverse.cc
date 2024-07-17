#include "src/make/traverse.h"

#include <map>
#include <memory>

namespace scud::api::internal {
ScudProject traverse(ast::AST& scudAst) {
  ScudProject project{};
  // std::map<std::string, > map{};
  for (auto& statement : scudAst.expressions()) {
    switch (statement.kind) {
      case ast::ExprKind::Function: {
        auto fun = static_cast<ast::FunctionExpr*>(&statement);
        if (fun->name == "project") {
          // render project
        } else if (fun->name == "executable") {
        }
      } break;

      case ast::ExprKind::Variable: {
        auto var = static_cast<ast::VariableExpr*>(&statement);
      } break;
      default:
        break;
    }
  }
}

namespace {
std::string ast_string_to_str(ast::StringExpr& expr) { return expr.val; }
}  // namespace

namespace {
enum ValueKind { String, Identifier };
struct Value {
  std::string value;
  bool identifier;
};
std::vector<Value> ast_list_to_list(ast::ListExpr expr) {
  std::vector<Value> values{};
  for (auto& v : expr.values) {
    switch (v.get()->kind) {
      case ast::ExprKind::Identifier: {
        auto ident = static_cast<ast::IdentifierExpr*>(v.get());
        values.push_back(Value{.identifier = true, .value = ident->name});
      } break;
      case ast::ExprKind::String: {
        auto ident = static_cast<ast::StringExpr*>(v.get());
        values.push_back(Value{.identifier = false, .value = ident->val});
      } break;
      default:
        break;
    }
  }
  return values;
}
}  // namespace
}  // namespace scud::api::internal
