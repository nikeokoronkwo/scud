#ifndef _SCUD_LIB_BASE_H
#define _SCUD_LIB_BASE_H

// TODO: Add scud namespace

namespace scud {
namespace api {
enum ScudLibraryType { Shared, Static, Object };

enum ScudLibraryScope : bool { Private = true, Public = false };
}  // namespace api
}  // namespace scud

#endif