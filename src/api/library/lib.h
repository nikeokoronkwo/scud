#ifndef _SCUD_LIB_H
#define _SCUD_LIB_H

#include <vector>
#include <string>
#include <map>

#include "src/api/base/base.h"
#include "src/api/library/lib_base.h"

namespace scud {
  namespace api {

struct ScudLibrary: public ScudBasicTarget<ScudLibrary> {
    std::string name;
    ScudLanguage lang;
    ScudLibraryType type;
    std::vector<std::string> src;
    std::vector<ScudInclude> include;
    std::vector<ScudLibrary> libraries;
    bool debug;
    ScudLibraryScope scope;
    ScudDefines defines;
    std::vector<std::string> flags;

    std::string make() override;
};
  }
}

#endif