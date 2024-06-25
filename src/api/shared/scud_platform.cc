#include "scud_platform.h"

#include "library/lib_base.h"

const ScudPlatform currentPlatform() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  return Windows;
#elif __APPLE__
  return MacOS;
#elif __linux__
  return Linux;
#endif
  return Linux;
}