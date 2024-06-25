#include "src/api/library/lib_funcs.h"

namespace scud {
  namespace api {
    namespace internal {
std::string lib_extension(ScudLibraryType type, shared::ScudPlatform platform) {
  switch (type) {
    case Shared:
      if (platform == shared::Windows)
        return ".dll";
      else if (platform == shared::MacOS)
        return ".dylib";
      else
        return ".so";
    case Static:
      if (platform == shared::Windows)
        return ".lib";
      else
        return ".a";
    case Object:
      return ".o";
  }
}
    }
  }
}