#include "base.h"

namespace scud {
namespace api {

ScudLanguage parse_lang(std::string lang) {
  if (lang == "rust" || lang == "rs")
    return rust;
  else if (lang == "zig")
    return zig;
  else if (lang == "swift")
    return swift;
  else if (lang == "go" || lang == "golang")
    return go;
  else if (lang == "d" || lang == "dlang")
    return d;
  else if (lang == "c")
    return c;
  else if (lang == "cpp" || lang == "c++" || lang == "cxx" || lang == "cc")
    return cpp;
  else
    return undefined;
}

}  // namespace api
}  // namespace scud