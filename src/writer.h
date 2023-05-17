#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include "lapwing.h"

struct Writer {
    std::ofstream* assets; 
    size_t ToCLength;
    std::map<std::string, assettype> extensionsToType;

    Writer(std::string filename, size_t assetCount);

    void writeHash(Hash hash);

    void writeTableOfContents(ToCElement* ToC);

    uintptr_t writeAsset(ToCElement& content, std::string path);

    std::string getExtension(std::string path);

    ~Writer();
};
