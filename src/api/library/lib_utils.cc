#include "lib_utils.h"

#include <map>
#include <string>
#include <vector>

#include "src/api/library/lib_funcs.h"
#include "src/api/shared/shared_utils.h"

namespace scud {
   namespace api {
        namespace internal {
/**
 * Writes make command code for building a `ScudLibrary` object
 */
std::string build_cc_library(ScudLibrary lib) {
  // The output of the function as a string
  std::string output;

  // Get the desired c compiler
  std::string compiler = set_compiler_from_lang(lib.lang, lib.defines);

  // Set the output flag for the command
  std::string out =
      "-o " + lib.name + lib_extension(lib.type, shared::currentPlatform());

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

  // Add necessary flags (and/or extra commands) for building to a library
  if (lib.type == Shared) {
    // Add shared flag to make a shared library
    command_parts.insert(command_parts.begin() + 1, "-shared");
  } else if (lib.type == Object) {
    // Add Compile flag to generate an object
    command_parts.insert(command_parts.begin() + 1, "-c");
  } else {
    // Making a static library requires an archiver command to statically link
    // object files
    std::string static_lib_name = lib.src[0];
    command_parts[1] = "-o " + static_lib_name + ".o";
    command_parts.insert(command_parts.begin() + 1, "-c");
    command_parts.push_back(
        "\n\t" +
        (lib.defines.count("ARCHIVER") ? lib.defines["ARCHIVER"] : "ar") +
        " rcs " + (lib.name + lib_extension(lib.type, shared::currentPlatform())) +
        " " + (static_lib_name + ".o"));
  }

  // Merge and return
  output += merge_vec(command_parts, " ");
  return output;
}
}  // namespace scud
   }
}