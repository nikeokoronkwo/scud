#ifndef SCUD_AST_H
#define SCUD_AST_H

#include <string>
#include "src/compiler/parser.h"

ast::AST parse(const char* source);

ast::AST parse_file(const char* file);

#endif