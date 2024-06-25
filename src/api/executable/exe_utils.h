#ifndef _SCUD_EXE_UTILS_H
#define _SCUD_EXE_UTILS_H

#include <string>

#include "src/api/executable/exe.h"

namespace scud {
namespace api {
namespace internal {
std::string build_cc_executable(ScudExecutable lib);
std::string build_go_executable(ScudExecutable lib);
std::string build_rust_executable(ScudExecutable lib);
std::string build_d_executable(ScudExecutable lib);
std::string build_swift_executable(ScudExecutable lib);
std::string build_zig_executable(ScudExecutable lib);
}  // namespace internal
}  // namespace api

}  // namespace scud

#endif