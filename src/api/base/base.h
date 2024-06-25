#ifndef SCUD_BASE_H
#define SCUD_BASE_H

#include <string>
#include <map>

namespace scud {
    namespace api {

// A base enum for the different kinds of languages supported by Scud
enum ScudLanguage { 
    rust, 
    zig, 
    swift, 
    d, 
    c, 
    cpp, 
    go, 
    custom, 
    undefined
};

// include paths
typedef struct {
    std::string path;
    bool is_private;
} ScudInclude;

// define flags/env 
typedef std::map<std::string, std::string> ScudDefines;

// A base target, which could either be a library or executable
struct ScudTarget {
    std::string name;
    std::vector<std::string> src;
    ScudDefines defines;

    virtual std::string make() = 0;
};

// A basic Scud Target for Generic Targets (`executable`, `library` and other basic targets)
template<typename Lib>
struct ScudBasicTarget: public ScudTarget {
    ScudLanguage lang;
    std::vector<Lib> libraries;
    std::vector<ScudInclude> include;
    std::vector<std::string> flags;

    virtual std::string make() override = 0;
};


    // Parses the given language as a string of type `std::string` and returns a `ScudLanguage` type
    //
    // Used for conversion between the given types
    ScudLanguage parse_lang(std::string lang);

    }
}


#endif