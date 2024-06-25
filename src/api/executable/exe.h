#ifndef _SCUD_EXE_BASE_H
#define _SCUD_EXE_BASE_H

#include <string>
#include <vector>

#include "src/api/base/base.h"
#include "src/api/library/lib.h"

// TODO: Add scud namespace

namespace scud::api {
struct ScudExecutable : public ScudBasicTarget<ScudLibrary> {
  std::string name;
  ScudLanguage lang;
  std::vector<std::string> src;
  std::vector<ScudInclude> include;
  std::vector<ScudLibrary> libraries;
  ScudDefines defines;
  std::vector<std::string> flags;

  std::string make() override;
};
}  // namespace scud::api

#endif