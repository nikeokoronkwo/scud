#ifndef SRC_MAKE_TRAVERSE_H_
#define SRC_MAKE_TRAVERSE_H_

#include "src/api/project.h"
#include "src/compiler/parser.h"

namespace scud::api::internal {
      ScudProject traverse(ast::AST& scudAst);
    }

#endif