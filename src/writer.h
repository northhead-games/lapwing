#pragma once
#include <fstream>
#include <iostream>
#include <map>

#include "lapwing.h"
#include "file_utils.h"

struct Writer {
    std::ofstream* assets; 
    size_t ToCLength;
    std::map<std::string, AssetType> extensionsToType;

    Writer(std::string filename, size_t assetCount);

    void writeHash(Hash hash);

    void writeTableOfContents(Entry* ToC);

    uintptr_t writeAsset(Entry& content, std::string path);

    ~Writer();
};
