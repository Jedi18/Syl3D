#include "fileio.h"

using namespace utility;

std::vector<std::string> FileIO::filesInPath(const std::string& path) {
    std::vector<std::string> filesList;
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        filesList.push_back(entry.path().filename().string());
    }

    return filesList;
}