#include "fuctions.h"

uint32_t bytesToMB(uint32_t bytes){
	return bytes / 1048576;
}

uint32_t mbToBytes(uint32_t mBytes){
	return mBytes * 1048576;
}
