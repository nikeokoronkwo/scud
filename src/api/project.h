#ifndef SCUD_SRC_API_PROJECT_H
#define SCUD_SRC_API_PROJECT_H

#include <vector>
#include <map>

#include "src/api/base/base.h"

namespace scud {
namespace api {
struct ScudProject {
  std::string name;
  ScudDefines defines;

  std::map<std::string, ScudTarget> targets;

  std::vector<std::string> make();
};
}  // namespace api
}  // namespace scud

#endif