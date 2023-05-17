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

enum assettype {
	IMAGE,
	MODEL,
};

typedef struct ToCElement {
	u64 hash;
	assettype type;
	uintptr_t offset;
	uintptr_t size;

	bool operator < (const ToCElement& comp) const {
		return (hash < comp.hash);
	}
} ToCElement;

typedef struct imageStruct {
	int width;
	int height;
	int bitDepth;
} imageStruct;

enum vertexattrib {
	POS = 1,
	NORM = 2,
	TAN = 4,
	TEX = 8,
};

typedef struct vec3 {
	float x;
	float y;
	float z;
} vec3;

typedef struct vec2 {
	float x;
	float y;
} vec2;

typedef struct modelStruct {
	u64 vertexCount;
	u8 vertexAttributes;
} modelStruct;
