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

void Writer::writeTableOfContents(Entry* ToC) {
	assets->seekp(sizeof(Hash), std::ios_base::beg);
	assets->write((char*)ToC, ENTRY_SIZE * ToCLength);
}

uintptr_t Writer::writeAsset(Entry& content, std::string path) {
	assets->seekp(content.offset, std::ios_base::beg);
	std::string ext = getExtension(path);

	if (extensionsToType[ext] == assettype::IMAGE) {
		content.type = assettype::IMAGE;
		imageInfo imageInfo = {};
		if (fileExists(path)) {
			unsigned char* image = stbi_load(path.c_str(), &imageInfo.width, &imageInfo.height, &imageInfo.bitDepth, 0);
			assets->write((char*)&imageInfo, sizeof(imageInfo));
			assets->write((char*)image, imageInfo.width * imageInfo.height * imageInfo.bitDepth);
			stbi_image_free(image);
			content.size = sizeof(imageInfo) + imageInfo.width * imageInfo.height * imageInfo.bitDepth;
			return content.offset + content.size;
		} else {
			std::cerr << "Asset file " << path << " does not exists." << std::endl;
		}
	}
	return -1;
}

Writer::~Writer() {
	assets->close();
};