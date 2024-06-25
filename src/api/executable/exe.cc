#include "src/api/executable/exe.h"

#include <string>
#include <vector>

#include "src/api/build_targets/c.h"
#include "src/api/executable/exe_funcs.h"
#include "src/api/shared/scud_platform.h"
#include "src/api/shared/shared_utils.h"

namespace scud::api::__internal {
std::string build_command_from_exe(ScudExecutable exe) {
  std::string compiler =
      internal::set_compiler_from_lang(exe.lang, exe.defines);

  switch (exe.lang) {
    case c:
    case cpp: {
      std::vector<std::string> includes;
      std::transform(exe.include.cbegin(), exe.include.cend(),
                     std::back_inserter(includes),
                     [](ScudInclude& include) { return include.path; });
      return CExecutable(compiler, exe.name, includes, exe.src).make();
    } break;
    default:
      return "";
      break;
  }
}

std::string make_executable(ScudExecutable exe) {
  // The name of the target
  std::string target =
      exe.name + internal::exe_extension(shared::currentPlatform());

  // The required arguments
  std::vector<std::string> require = exe.src;

  // TODO: Add libraries

  std::string command = build_command_from_exe(exe);

  // Combine and return
  return target + ": " + internal::merge_vec(require, " ") + "\n\t" + command +
         "\n";
}
}  // namespace scud::api::__internal

namespace scud::api {
std::string ScudExecutable::make() {
  return __internal::make_executable(*this);
}
}  // namespace scud::api
