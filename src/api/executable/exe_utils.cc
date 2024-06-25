#include "src/api/executable/exe_utils.h"

#include "src/api/executable/exe_funcs.h"
#include "src/api/shared/shared_utils.h"

namespace scud::api::internal {
std::string build_cc_executable(ScudExecutable lib) {
  // The output of the function as a string
  std::string output;

  // Get the desired c compiler
  std::string compiler = set_compiler_from_lang(lib.lang, lib.defines);

  // Set the output flag for the command
  std::string out = "-o " + lib.name + exe_extension(shared::currentPlatform());

  // Merge the sources as a single string
  std::string sources = merge_vec(lib.src, " ");

  // Derive the include paths and merge them as single string
  std::string include_paths = "";

  for (int i = 0; i < lib.include.size(); ++i) {
    include_paths += ("-I" + lib.include[i].path);
    if (i + 1 != lib.include.size()) include_paths += " ";
  }

  // Set the parts as a vector to merge
  std::vector<std::string> command_parts = {compiler, out, sources};
  if (include_paths != "")
    command_parts.insert(command_parts.end() - 1, include_paths);

  // Merge and return
  output += merge_vec(command_parts, " ");
  return output;
}
}  // namespace scud::api::internal