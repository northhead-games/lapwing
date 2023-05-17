#include "hasher.h"
#include <cmath>

Hash findPerfectHash(std::vector<std::string> assets) {
	u32 startAmount = 1;
	u32 endAmount = 0;
	u32 prime = 31;
	bool incStart = false;

	while (true) {
		std::set<u64> hashes;
		for each (auto assetFull in assets) {
			std::string asset = getBasename(assetFull);

			u32 power = 1;
			u64 hash = asset.length();
			u64 assetLen = asset.length();

			for (size_t i = 0; i < startAmount; i++) {
				hash += (static_cast<u64>(asset[i % assetLen]) - 33) * static_cast<u64>(std::pow(prime, power++));
			}

			for (size_t i = 0; i < endAmount; i++) {
				hash += (static_cast<u64>(asset[(assetLen - i) % assetLen]) - 33) * static_cast<u64>(std::pow(prime, power++));
			}
			
			if (hashes.find(hash) != hashes.end()) {
				hashes.clear();
				if (incStart) {
					startAmount++;
				} else {
					endAmount++;
				}
				incStart = !incStart;
			} else {
				hashes.insert(hash);
			}
		}
		if (hashes.size() == assets.size()) {
			break;
		}
	}

	Hash hash = {};
	hash.assetCount = assets.size();
	hash.startChars = startAmount;
	hash.endChars = endAmount;
	hash.prime = prime;

	return hash;
}

u64 hashAsset(Hash hash, std::string name) {
	std::string asset = getBasename(name);
	u32 power = 1;
	u64 value = asset.length();
	u64 assetLen = asset.length();

	for (size_t i = 0; i < hash.startChars; i++) {
		value += (static_cast<u64>(asset[i % assetLen]) - 33) * static_cast<u64>(std::pow(hash.prime, power++));
	}
	for (size_t i = 0; i < hash.endChars; i++) {
		value += (static_cast<u64>(asset[(assetLen - i) % assetLen]) - 33) * static_cast<u64>(std::pow(hash.prime, power++));
	}

	return value;
}

std::string getBasename(std::string name) {
	#if _WIN32
	char fname[_MAX_FNAME];
	_splitpath_s(name.c_str(), NULL, 0, NULL, 0, fname, _MAX_FNAME, NULL, 0);
	std::string asset(fname);
	#else
	char* fname = basename(name.c_str());
	std::string asset(fname);
	size_t extensionIndex = asset.find_last_of(".");
	if (extensionIndex != std::string::npos) asset = asset.substr(0, extensionIndex);
	#endif

	return asset;
}