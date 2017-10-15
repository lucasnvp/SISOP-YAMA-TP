#ifndef SETUP_H_
#define SETUP_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>

#include "commons/log.h"

typedef struct BinType{
	uint32_t fd;
	uint32_t size;
	char* binmap;
} t_bin;

t_bin* setup(char* RUTA_DATABIN, t_log* log_Console);
t_bin* data_setup(char* RUTA_DATABIN, t_log* log_Console);

#endif /* SETUP_H_ */
