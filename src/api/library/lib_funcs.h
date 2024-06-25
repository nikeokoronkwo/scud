#ifndef _SCUD_LIB_FUNCS_H
#define _SCUD_LIB_FUNCS_H

#include <string>

#include "src/api/library/lib.h"
#include "src/api/shared/scud_platform.h"

namespace scud {
  namespace api {
    namespace internal {
      std::string lib_extension(ScudLibraryType type, shared::ScudPlatform platform);
    }
  }
}



#endif