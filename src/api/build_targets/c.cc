#include "src/api/build_targets/c.h"

#include <string>
#include <vector>

#include "src/api/executable/exe_funcs.h"
#include "src/api/library/lib_funcs.h"
#include "src/api/shared/shared_utils.h"

namespace scud::api {
std::string CLibrary::make() {
  // The output of the function as a string
  std::string output;

  // Get the desired c compiler
  std::string compiler = this->compiler;

  std::string extension =
      internal::lib_extension(this->lib_type, shared::currentPlatform());

  // Set the output flag for the command
  std::string out = "-o " + this->output + extension;

  // Merge the sources as a single string
  std::string sources = internal::merge_vec(this->sources, " ");

  // Derive the include paths and merge them as single string
  std::string include_paths = "";

  for (int i = 0; i < this->include_paths.size(); ++i) {
    include_paths += ("-I" + this->include_paths[i]);
    if (i + 1 != this->include_paths.size()) include_paths += " ";
  }

  // Set the parts as a vector to merge
  std::vector<std::string> command_parts = {compiler, out, sources};
  if (include_paths != "")
    command_parts.insert(command_parts.end() - 1, include_paths);

  switch (this->lib_type) {
    case Shared:
      command_parts.insert(command_parts.begin() + 1, "-shared");
      break;
    case Object:
      command_parts.insert(command_parts.begin() + 1, "-c");
      break;
    case Static: {
      std::string static_lib_name = this->sources[0];
      command_parts[1] = "-o " + static_lib_name + ".o";
      command_parts.insert(command_parts.begin() + 1, "-c");
      command_parts.push_back("\n\t" + (this->archiver) + " rcs " +
                              (this->output + extension) + " " +
                              (static_lib_name + ".o"));
      break;
    }
    default:
      break;
  }

  // Merge and return
  output += internal::merge_vec(command_parts, " ");
  return output;
}

std::string CExecutable::make() {
  // The output of the function as a string
  std::string output;

  // Get the desired c compiler
  std::string compiler = this->compiler;

  std::string extension = internal::exe_extension(shared::currentPlatform());

  // Set the output flag for the command
  std::string out = "-o " + this->output + extension;

  // Merge the sources as a single string
  std::string sources = internal::merge_vec(this->sources, " ");

  // Derive the include paths and merge them as single string
  std::string include_paths = "";

  for (int i = 0; i < this->include_paths.size(); ++i) {
    include_paths += ("-I" + this->include_paths[i]);
    if (i + 1 != this->include_paths.size()) include_paths += " ";
  }

  // Set the parts as a vector to merge
  std::vector<std::string> command_parts = {compiler, out, sources};
  if (include_paths != "")
    command_parts.insert(command_parts.end() - 1, include_paths);

  // Merge and return
  output += internal::merge_vec(command_parts, " ");
  return output;
}
}  // namespace scud::api
