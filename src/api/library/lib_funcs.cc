#include "src/api/library/lib_funcs.h"

std::string lib_extension(ScudLibraryType type, ScudPlatform platform) {
  switch (type) {
    case Shared:
      if (platform == Windows)
        return ".dll";
      else if (platform == MacOS)
        return ".dylib";
      else
        return ".so";
    case Static:
      if (platform == Windows)
        return ".lib";
      else
        return ".a";
    case Object:
      return ".o";
  }
}