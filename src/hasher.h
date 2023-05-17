#include "lapwing.h"
#include <vector>
#include <set>
#include <string>

Hash findPerfectHash(std::vector<std::string> assets);

std::string getBasename(std::string name);

u64 hashAsset(Hash hash, std::string name);