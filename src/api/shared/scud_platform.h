#ifndef SCUD_PLATFORM_H
#define SCUD_PLATFORM_H

#include "library/lib_base.h"

enum ScudPlatform { Windows, MacOS, Linux };

const ScudPlatform currentPlatform();

#endif