#include "file_utils.h"

std::string getExtension(fs::path path) {
	return path.extension().string();
}

std::string getBasename(fs::path path) {
	return path.stem().string();
}

bool fileExists(fs::path path) {
	return fs::exists(path);
}
