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

// Variables hilos
pthread_t thread_server;

uint32_t SERVIDOR_FILESYSTEM;

void connect_server_FileSystem();
void init_log(char* pathLog);
void server(void* args);
void connection_handler(uint32_t socket, uint32_t command);

#endif /* YAMA_H_ */
