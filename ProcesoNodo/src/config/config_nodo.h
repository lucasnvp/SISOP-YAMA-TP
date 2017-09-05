#ifndef CONFIG_NODO_H_
#define CONFIG_NODO_H_

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "commons/string.h"
#include "commons/config.h"
#include "commons/log.h"

typedef struct ConfigType{
	uint32_t PUERTO_FILESYSTEM;
	char* IP_FILESYSTEM;
	char* NOMBRE_NODO;
	uint32_t PUERTO_WORKER;
	uint32_t PUERTO_DATANODE;
	char* RUTA_DATABIN;
} Type_Config;

Type_Config load_config(char* path);
void print_config(Type_Config auxConfig, t_log* log_Console);

#endif /* CONFIG_NODO_H_ */
