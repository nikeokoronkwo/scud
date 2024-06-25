#ifndef _SCUD_EXE_BASE_H
#define _SCUD_EXE_BASE_H

#include <vector>
#include <string>

#include "src/api/library/lib.h"
#include "src/api/base/base.h"

// TODO: Add scud namespace

struct ScudExecutable: public ScudBasicTarget<ScudLibrary> {
    std::string name;
    ScudLanguage lang;
    std::vector<std::string> src;
    std::vector<ScudInclude> include;
    std::vector<ScudLibrary> libraries;
    ScudDefines defines;
    std::vector<std::string> flags;

    std::string make() override;
};

#endif