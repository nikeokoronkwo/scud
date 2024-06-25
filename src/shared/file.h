#ifndef _SCUD_INTERNAL_FILE_H
#define _SCUD_INTERNAL_FILE_H

#include <string>
#include <vector>

namespace scud {
  namespace __utils {
    std::string read_file(std::string &dest, const char* const filename);
    std::vector<std::string> read_file_lines(std::vector<std::string> &dest, const char* const filename, bool overwrite = false);
  }
};


#endif