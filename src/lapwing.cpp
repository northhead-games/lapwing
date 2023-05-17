#include <iostream>
#include <sys/stat.h>
#include <algorithm>
#include "lz4.h"
#include "lapwing.h"
#include "reader.h"
#include "hasher.h"
#include "writer.h"

int main(int argc, char** argv) {
    if (argc == 1 || argc > 2) {
        std::cerr << "Usage: lapwing <file_containing_list_of_assets>" << std::endl;
        exit(1);
    }

    struct stat assetFile;
    if (stat(argv[1], &assetFile) != 0) {
        std::cerr << "Asset list cannot be found." << std::endl;
        exit(1);
    }

    std::vector assets = readAssetList(argv[1]);
    Hash perfectHash = findPerfectHash(assets);
    ToCElement* tableOfContents = (ToCElement*) calloc(perfectHash.assetCount, sizeof(ToCElement));
    Writer writer("assets.plv", perfectHash.assetCount);
    writer.writeHash(perfectHash);

    uintptr_t offset = sizeof(Hash) + sizeof(ToCElement) * perfectHash.assetCount;
    for (size_t i = 0; i < perfectHash.assetCount; i++) {
        tableOfContents[i].hash = hashAsset(perfectHash, assets[i]); 
        tableOfContents[i].offset = offset;        
        offset = writer.writeAsset(tableOfContents[i], assets[i]);
		printf("Name: %s\nHash: %zu\nSize: %zu\nOffset: %zu\n", assets[i].c_str(), tableOfContents[i].hash, tableOfContents[i].size, tableOfContents[i].offset);
    }

    std::sort(tableOfContents, tableOfContents + perfectHash.assetCount);
    writer.writeTableOfContents(tableOfContents);

    printf("Prime: %d\nStart Amount: %d\nEnd Amount: %d\nAsset Count: %zd\n", perfectHash.prime, perfectHash.startChars, perfectHash.endChars, perfectHash.assetCount);

    free(tableOfContents);
}
