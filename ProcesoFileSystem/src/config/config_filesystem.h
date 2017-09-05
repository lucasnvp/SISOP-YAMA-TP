#ifndef CONFIG_FILESYSTEM_H_
#define CONFIG_FILESYSTEM_H_

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "commons/string.h"
#include "commons/config.h"
#include "commons/log.h"

typedef struct ConfigType{
	uint32_t PUERTO_FILESYSTEM;
} Type_Config;

Type_Config load_config(char* path);
void print_config(Type_Config auxConfig, t_log* log_Console);

#endif /* CONFIG_FILESYSTEM_H_ */
