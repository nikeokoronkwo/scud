#ifndef _SCUD_SRC_API_INTERNAL_GENERIC_H_
#define _SCUD_SRC_API_INTERNAL_GENERIC_H_

#include <string>

namespace scud::api {
struct BuildTarget {
  std::string compiler;
  std::string output;

  BuildTarget(std::string compiler, std::string output = "out"): compiler(compiler), output(output) {}

  virtual std::string make() = 0;
};
}  // namespace scud::api

#endif