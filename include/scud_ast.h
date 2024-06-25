#ifndef SCUD_AST_H
#define SCUD_AST_H

#include <string>
#include "src/compiler/parser.h"

scud::ast::AST parse(const char* source);

scud::ast::AST parse_file(const char* file);

#endif