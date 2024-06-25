#ifndef _SCUD_EXE_FUNCS_H
#define _SCUD_EXE_FUNCS_H

#include <string>

#include "src/api/shared/scud_platform.h"

namespace scud {
namespace api {
namespace internal {
std::string exe_extension(shared::ScudPlatform platform);
}
}  // namespace api
}  // namespace scud

#endif