#include "writer.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Writer::Writer(std::string filename, size_t assetCount) {
	assets = new std::ofstream(filename, std::ofstream::out | std::ofstream::binary);
	ToCLength = assetCount;

	// Images
	extensionsToType["png"] = assettype::IMAGE;
	extensionsToType["jpg"] = assettype::IMAGE;
	extensionsToType["jpeg"] = assettype::IMAGE;
	extensionsToType["bmp"] = assettype::IMAGE;
	extensionsToType["hdr"] = assettype::IMAGE;
	extensionsToType["psd"] = assettype::IMAGE;
	extensionsToType["tga"] = assettype::IMAGE;
	extensionsToType["gif"] = assettype::IMAGE;
	extensionsToType["pic"] = assettype::IMAGE;
	extensionsToType["pgm"] = assettype::IMAGE;
	extensionsToType["ppm"] = assettype::IMAGE;
}

void Writer::writeHash(Hash hash) {
	assets->seekp(0, std::ios_base::beg);
	assets->write((char*) &hash, sizeof(Hash));
}

void Writer::writeTableOfContents(ToCElement* ToC) {
	assets->seekp(sizeof(Hash), std::ios_base::beg);
	assets->write((char*)ToC, sizeof(ToCElement) * ToCLength);
}

uintptr_t Writer::writeAsset(ToCElement& content, std::string path) {
	assets->seekp(content.offset, std::ios_base::beg);
	std::string ext = getExtension(path);

	if (extensionsToType[ext] == assettype::IMAGE) {
		content.type = assettype::IMAGE;
		imageStruct imStruct = {};
		unsigned char* image = stbi_load(path.c_str(), &imStruct.width, &imStruct.height, &imStruct.bitDepth, 0);
		assets->write((char*)&imStruct, sizeof(imageStruct));
		assets->write((char*) image, imStruct.width * imStruct.height * imStruct.bitDepth);
		stbi_image_free(image);
		content.size = sizeof(imageStruct) + imStruct.width * imStruct.height * imStruct.bitDepth;
		return content.offset + content.size;
	}
	return -1;
}

std::string Writer::getExtension(std::string path) {
	#if _WIN32
	char ext[_MAX_EXT];
	_splitpath_s(path.c_str(), NULL, 0, NULL, 0, NULL, 0, ext, _MAX_EXT);
	std::string asset(ext);
	#else
	char* ext = basename(name.c_str());
	std::string asset(fname);
	size_t extensionIndex = asset.find_last_of(".");
	if (extensionIndex != std::string::npos) asset = asset.substr(extensionIndex + 1, asset.length());
	#endif

	return ext;
}

Writer::~Writer() {
	assets->close();
};