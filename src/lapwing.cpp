#include <iostream>
#include <algorithm>

#include "lz4.h"
#include "lapwing.h"
#include "reader.h"
#include "hasher.h"
#include "writer.h"
#include "file_utils.h"

int main(int argc, char** argv) {
    if (argc == 1 || argc > 2) {
        std::cerr << "Usage: lapwing <file_containing_list_of_assets>" << std::endl;
        exit(1);
    }

    if (!fileExists(argv[1])) {
        std::cerr << "Asset list cannot be found." << std::endl;
        exit(1);
    }

    std::vector assets = readAssetList(argv[1]);
    Hash hash = findPerfectHash(assets);
    Entry* tableOfContents = (Entry*) calloc(hash.assetCount, ENTRY_SIZE);
    Writer writer("assets.plv", hash.assetCount);
    writer.writeHash(hash);

    uintptr_t offset = HASH_SIZE + ENTRY_SIZE * hash.assetCount;
    for (size_t i = 0; i < hash.assetCount; i++) {
        tableOfContents[i].hash = hashAsset(hash, assets[i]); 
        tableOfContents[i].offset = offset;        
        offset = writer.writeAsset(tableOfContents[i], assets[i]);
		printf("Name: %s\nHash: %zu\nSize: %zu\nOffset: %zu\n", assets[i].c_str(), tableOfContents[i].hash, tableOfContents[i].size, tableOfContents[i].offset);
    }

    std::sort(tableOfContents, tableOfContents + hash.assetCount);
    writer.writeTableOfContents(tableOfContents);

    printf("Prime: %d\nStart Amount: %d\nEnd Amount: %d\nAsset Count: %zd\n", hash.prime, hash.startChars, hash.endChars, hash.assetCount);

    free(tableOfContents);
}
