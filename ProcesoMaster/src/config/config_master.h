#ifndef CONFIG_MASTER_H_
#define CONFIG_MASTER_H_

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "commons/string.h"
#include "commons/config.h"
#include "commons/log.h"

typedef struct ConfigType{
	uint32_t YAMA_PUERTO;
	char* YAMA_IP;
} Type_Config;

Type_Config load_config(char* path);
void print_config(Type_Config auxConfig, t_log* log_Master);

#endif /* CONFIG_MASTER_H_ */
