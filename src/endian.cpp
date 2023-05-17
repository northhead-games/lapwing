#include "endian.h"

#if _WIN32
u16 byteswap_16(u16 x) {
	return _byteswap_ushort(x);
}
u32 byteswap_32(u32 x) {
	return _byteswap_ulong(x);
}
u64 byteswap_64(u64 x) {
	return _byteswap_uint64(x);
}
#else
u16 byteswap_16(u16 x) {
	return bswap_16(x);
}
u32 byteswap_32(u32 x) {
	return bswap_32(x);
}
u64 byteswap_64(u64 x) {
	return bswap_64(x);
}
#endif
