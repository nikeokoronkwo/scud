#include <string>
#include <fstream>
#include <iostream>
#include <vector>

namespace scud {
	namespace __utils {


std::string read_file(std::string &dest, const char* const filename) {
    std::ifstream ifile(filename, std::ios::ate | std::ios::binary);
    if (ifile.is_open()) {
	int length = ifile.tellg();
	ifile.seekg(0, std::ios_base::beg);
	// TODO: Don't use +1
	char buffer[length+1];
	try
        {
            ifile.read(buffer, length);
	    dest = buffer;
	    ifile.close();
	    return buffer;
        }
        catch(std::ios_base::failure &)
        {
            std::cout << "File cannot be read" << std::endl;
	    ifile.close();
        }
	return "";
    } else {
	std::cerr << "Unable to find file:" << filename << ".\nPlease check if the file exists in the given directory" << std::endl;
    return "";
    }
}

std::vector<std::string> read_file_lines(std::vector<std::string> &dest, const char* const filename, bool overwrite = false) {
    std::ifstream ifile(filename);
    if (ifile.is_open()) {
	if (overwrite) dest.clear();
	std::string line;
	while (getline(ifile, line)) {
	    dest.push_back(line);
	}
	ifile.close();
	return dest;
    } else {
	std::cerr << "Unable to find file:" << filename << ".\nPlease check if the file exists in the given directory" << std::endl; 
    }
    return std::vector<std::string>();
}

}
}