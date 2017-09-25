#include "fuctions.h"

uint32_t bytesToMB(uint32_t bytes){
	return bytes / 1048576;
}

uint32_t mbToBytes(uint32_t mBytes){
	return mBytes * 1048576;
}

uint32_t ValidarArchivo(char* path){
	uint32_t archivo_existente;
	if(access(path, F_OK) != -1){
		archivo_existente = true;
	} else{
		archivo_existente = false;
	}
	return archivo_existente;
}
