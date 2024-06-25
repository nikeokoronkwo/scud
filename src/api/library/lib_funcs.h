#ifndef _SCUD_LIB_FUNCS_H
#define _SCUD_LIB_FUNCS_H

#include <string>

#include "src/api/library/lib.h"
#include "src/api/shared/scud_platform.h"

std::string lib_extension(ScudLibraryType type, ScudPlatform platform);

#endif