#ifndef SCUD_SRC_API_PROJECT_H
#define SCUD_SRC_API_PROJECT_H

#include <vector>
#include "src/api/base/base.h"

struct ScudProject {
  std::string name;
  ScudDefines defines;

  std::vector<ScudTarget> targets;

  std::vector<std::string> make();
};

#endif