#pragma once
#include <stdint.h>

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef int64_t  i64;
typedef int32_t  i32;
typedef int16_t  i16;
typedef int8_t   i8;

typedef double   f64;
typedef float    f32;

typedef struct Hash {
	u32 prime;
	u32 startChars;
	u32 endChars;
	size_t assetCount;
} Hash;

#define HASH_SIZE sizeof(Hash)

enum assettype {
	IMAGE,
	MODEL,
};

typedef struct Entry {
	u64 hash;
	uintptr_t offset;
	uintptr_t size;
	assettype type;

	bool operator < (const Entry& comp) const {
		return (hash < comp.hash);
	}
} Entry;

#define ENTRY_SIZE sizeof(Entry)

typedef struct imageInfo {
	int width;
	int height;
	int bitDepth;
} imageInfo;

typedef struct vec3 {
	float x;
	float y;
	float z;
} vec3;

typedef struct vec2 {
	float x;
	float y;
} vec2;

enum vertexAttrib {
	POS = 1,
	NORM = 2,
	TAN = 4,
	TEX = 8,
};

typedef struct modelInfo {
	u64 vertexCount;
	u8 vertexAttributes;
} modelInfo;
