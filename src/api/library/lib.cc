#include "src/api/library/lib.h"

#include <algorithm>
#include <string>
#include <vector>

#include "src/api/build_targets/c.h"
#include "src/api/library/lib_funcs.h"
#include "src/api/shared/scud_platform.h"
#include "src/api/shared/shared_utils.h"

namespace scud::api::__internal {
std::string build_command_from_lib(ScudLibrary lib) {
  std::string compiler =
      internal::set_compiler_from_lang(lib.lang, lib.defines);

  switch (lib.lang) {
    case c:
    case cpp: {
      std::vector<std::string> includes;
      std::transform(lib.include.cbegin(), lib.include.cend(),
                     std::back_inserter(includes),
                     [](ScudInclude& include) { return include.path; });
      return CLibrary(compiler, lib.type, lib.name, includes, lib.src,
                      (lib.defines.count("ARCHIVER") ? lib.defines["ARCHIVER"]
                                                     : "ar"))
          .make();
    }

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