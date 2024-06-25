#include "src/api/executable/exe_funcs.h"

#include <string>

#include "src/api/shared/scud_platform.h"

std::string exe_extension(ScudPlatform platform) {
  switch (platform) {
    case Windows:
      return ".exe";
      break;

    default:
      return "";
      break;
  }
}