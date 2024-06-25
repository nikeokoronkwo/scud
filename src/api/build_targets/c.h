#ifndef _SCUD_SRC_API_INTERNAL_C_H_
#define _SCUD_SRC_API_INTERNAL_C_H_

#include <string>
#include <vector>

#include "src/api/build_targets/generic.h"
#include "src/api/library/lib_base.h"

namespace scud::api {
struct CTarget : public BuildTarget {
  std::vector<std::string> include_paths;
  std::vector<std::string> sources;
  

  CTarget(std::string compiler, std::string output = "out", std::vector<std::string> include_paths = {}, std::vector<std::string> sources = {}):
    BuildTarget(compiler, output), include_paths(include_paths), sources(sources) {}

  virtual std::string make() override = 0;
};

struct CLibrary : public CTarget {
  ScudLibraryType lib_type;
  std::string archiver;

  CLibrary(std::string compiler, ScudLibraryType lib_type, std::string output = "out", std::vector<std::string> include_paths = {}, std::vector<std::string> sources = {}, std::string archiver = "ar"):
    CTarget(compiler, output, include_paths, sources), lib_type(lib_type), archiver(archiver) {}

  std::string make() override;
};

struct CExecutable : public CTarget {
  std::string make() override;

  CExecutable(std::string compiler, std::string output = "out", std::vector<std::string> include_paths = {}, std::vector<std::string> sources = {}):
    CTarget(compiler, output, include_paths, sources) {}
};
}  // namespace scud::api

#endif