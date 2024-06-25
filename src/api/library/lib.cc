#include "src/api/library/lib.h"

#include <string>
#include <vector>

#include "src/api/library/lib_funcs.h"
#include "src/api/library/lib_utils.h"
#include "src/api/shared/scud_platform.h"
#include "src/api/shared/shared_utils.h"

namespace scud::api::__internal {
std::string build_command_from_lib(ScudLibrary lib) {
  switch (lib.lang) {
    case c:
    case cpp:
      return internal::build_cc_library(lib);
    default:
      return internal::set_compiler_from_lang(lib.lang) +
             internal::merge_vec(lib.src, " ") + "-o " + lib.name;
  }
}

std::string make_library(ScudLibrary lib) {
  // get target name
  std::string target =
      lib.name + internal::lib_extension(lib.type, shared::currentPlatform());

  // get required items
  std::vector<std::string> require = lib.src;

  // TODO: Add libraries

  // get command for library
  std::string command = build_command_from_lib(lib);

  // Combine and return
  return target + ": " + internal::merge_vec(require, " ") + "\n\t" + command +
         "\n";
}
}  // namespace scud::api::__internal

namespace scud {
namespace api {
std::string ScudLibrary::make() { return __internal::make_library(*this); }
}  // namespace api
}  // namespace scud