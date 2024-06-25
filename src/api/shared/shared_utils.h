#ifndef _SCUD_SHARED_UTILS_H
#define _SCUD_SHARED_UTILS_H

#include <string>
#include <vector>

#include "src/api/library/lib_base.h"

namespace scud {
namespace api {
namespace internal {

std::string merge_vec(std::vector<std::string> vec, std::string separator = "",
                      std::string precede = "");

std::string set_compiler_from_lang(ScudLanguage lang, ScudDefines defines = {});
}  // namespace internal
}  // namespace api
}  // namespace scud

#endif