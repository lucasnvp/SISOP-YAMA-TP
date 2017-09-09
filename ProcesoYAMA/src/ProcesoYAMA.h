#ifndef YAMA_H_
#define YAMA_H_

#include <stdio.h>
#include <stdlib.h>

#include "commons/log.h"

#include "config/config_yama.h"

#define NUEVA_CONEXION_YAMA 2

char* PATH_CONFIG = "/home/utnso/Blacklist/tp-2017-2c-Blacklist/ProcesoYAMA/src/config/config.txt";
Type_Config config;

char* PATH_LOG = "/home/utnso/Blacklist/Logs/logYAMA.txt";
t_log* log_Console;
t_log* log_YAMA;

uint32_t SERVIDOR_FILESYSTEM;

void connect_server_FileSystem();
void init_log(char* pathLog);

#endif /* YAMA_H_ */
