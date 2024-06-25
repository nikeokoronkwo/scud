#ifndef SCUD_PLATFORM_H
#define SCUD_PLATFORM_H

#include "src/api/library/lib_base.h"

namespace scud {
namespace api {
namespace shared {

enum ScudPlatform { Windows, MacOS, Linux };

const ScudPlatform currentPlatform();

}  // namespace shared
}  // namespace api
}  // namespace scud

#endif