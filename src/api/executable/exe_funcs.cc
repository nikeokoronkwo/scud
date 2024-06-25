#include "src/api/executable/exe_funcs.h"

#include <string>

#include "src/api/shared/scud_platform.h"

namespace scud {
  namespace api {
    namespace internal {
std::string exe_extension(shared::ScudPlatform platform) {
  switch (platform) {
    case shared::Windows:
      return ".exe";
      break;

    default:
      return "";
      break;
  }
}
    }
  }
}