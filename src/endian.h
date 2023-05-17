#if _WIN32
#include <stdlib.h>
#else
#include <byteswap.h>
#endif

#include "lapwing.h"

enum endianness {
	little = 0,
	big = 1,
};

inline endianness get_system_endianness()
{
	const int value{ 0x01 };
	const void* address{ static_cast<const void*>(&value) };
	const unsigned char* least_significant_address{ static_cast<const unsigned char*>(address) };

	return (*least_significant_address == 0x01) ? endianness::little : endianness::big;
}

u16 byteswap_16(u16 x);
u32 byteswap_32(u32 x);
u64 byteswap_64(u64 x);
