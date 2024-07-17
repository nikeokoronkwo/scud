#include "src/api/project.h"

#include <algorithm>
#include <map>
#include <string>
#include <vector>

namespace scud::api {
std::vector<std::string> ScudProject::make() {
  std::vector<ScudTarget> values;
  for (auto it = targets.begin(); it != targets.end(); ++it) {
    values.push_back(it->second);
  }

  std::vector<std::string> output{};

  std::transform(values.cbegin(), values.cend(), std::back_inserter(output),
                 [](ScudTarget target) { return target.make(); });

  return output;
}
}  // namespace scud::api