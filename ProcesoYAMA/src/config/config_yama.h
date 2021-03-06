#ifndef CONFIG_YAMA_H_
#define CONFIG_YAMA_H_

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "commons/string.h"
#include "commons/config.h"
#include "commons/log.h"

typedef struct ConfigType{
	uint32_t YAMA_PUERTO;
	uint32_t FS_PUERTO;
	char* FS_IP;
	uint32_t RETARDO_PLANIFICACION;
	char* ALGORITMO_BALANCEO;
	uint32_t CANTCONEXIONES;
} Type_Config;

Type_Config load_config(char* path);
void print_config(Type_Config auxConfig, t_log* log_Console);

#endif /* CONFIG_YAMA_H_ */
