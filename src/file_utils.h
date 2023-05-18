#pragma once
#include <filesystem>
#include <string>
namespace fs = std::filesystem;

std::string getExtension(fs::path path);

std::string getBasename(fs::path path);

bool fileExists(fs::path path);
