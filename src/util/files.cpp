#include "files.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>

std::optional<std::string> origo::util::read_file(std::string path) {
    if (!std::filesystem::exists(path)) {
        return {};
    }

    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string string = buffer.str();

    return string;
}
