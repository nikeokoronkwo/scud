#include "src/api/project.h"

#include <algorithm>
#include <string>

namespace scud::api {
std::vector<std::string> ScudProject::make() {
  std::vector<std::string> output;

  std::transform(targets.cbegin(), targets.cend(), std::back_inserter(output),
                 [](ScudTarget& target) { return target.make(); });

  return output;
}
}  // namespace scud::api