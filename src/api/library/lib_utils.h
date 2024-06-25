#ifndef _SCUD_LIB_UTILS_H
#define _SCUD_LIB_UTILS_H

#include <string>
#include "lib_base.h"

namespace scud {
    std::string build_cc_library(ScudLibrary lib);
    std::string build_go_library(ScudLibrary lib);
    std::string build_rust_library(ScudLibrary lib);
    std::string build_d_library(ScudLibrary lib);
    std::string build_swift_library(ScudLibrary lib);
    std::string build_zig_library(ScudLibrary lib);
}

#endif