#include <iostream>

#include "scud_ast.h"

using namespace scud::ast;

int main() {
  AST ast = parse(R"(
project("scudderia", "0.1.0")

executable("foo", C, 
  src: ["foo.c"]
)
)");
  std::cout << ast.expressions().size();
}