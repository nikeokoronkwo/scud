// TODO: Replace with lower standard (C++20 -> C++11)

#include "src/api/shared/shared_utils.h"

#include <map>
#include <string>

#include "src/api/library/lib.h"


namespace scud {
  namespace api {
    namespace internal {

std::string set_compiler_from_lang(ScudLanguage lang, ScudDefines defines) {
  switch (lang) {
    case rust:
      return defines.count("RUST_COMPILER") ? defines["RUST_COMPILER"]
                                            : "rustc";
      break;
    case swift:
      return defines.count("SWIFT_COMPILER") ? defines["SWIFT_COMPILER"]
                                             : "swiftc";
      break;
    case go:
      return defines.count("GO_COMPILER") ? defines["GO_COMPILER"] : "go";
      break;
    case c:
      return defines.count("C_COMPILER") ? defines["C_COMPILER"] : "gcc";
      break;
    case cpp:
      return defines.count("CC_COMPILER") ? defines["CC_COMPILER"] : "g++";
      break;
    case d:
      return defines.count("D_COMPILER") ? defines["D_COMPILER"] : "d";
      break;
    case zig:
      return defines.count("ZIG_COMPILER") ? defines["ZIG_COMPILER"] : "zig";
      break;
    default:
      return "";
      break;
  }
}

std::string merge_vec(std::vector<std::string> vec, std::string separator,
                      std::string precede) {
  std::string s;
  for (int i = 0; i < vec.size(); ++i) {
    s += (precede + vec[i]);
    if (i + 1 != vec.size()) s += separator;
  }
  return s;
}
    }
  }
}