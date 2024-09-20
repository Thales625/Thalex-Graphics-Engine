#include "../../include/utils/utils.hpp"

#include <fstream>
#include <sstream>

std::string readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string content;
    std::stringstream fileStream;
    fileStream << file.rdbuf();
    file.close();
    content = fileStream.str();
    return content;
}
