#include "include/scud_ast.h"
#include "src/compiler/lexer.h"
#include "src/compiler/parser.h"
#include "src/shared/file.h"

using namespace scud;

ast::AST parse(const char* source) {
  Lexer lexer(source);
  std::vector<Token> tokens = lexer.scan_tokens();
  Parser parser(tokens);
  return parser.parse();
}

ast::AST parse_file(const char* file) {
  std::string source;
  __utils::read_file(source, file);

  return parse(source.c_str());
}