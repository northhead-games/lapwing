#include "reader.h"

std::vector<std::string> readAssetList(std::string pathToFile) {
    std::vector<std::string> assets;
    std::ifstream assetFile(pathToFile);
    if (assetFile.is_open()) {
        for (std::string line; getline(assetFile, line); ) {
            assets.push_back(line);
        }
    }
    return assets;
}
