#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "commons/log.h"
#include "servidor/servidor.h"
#include "serializador/serializador.h"
#include "readline/readline.h"
#include "readline/history.h"

#include "config/config_filesystem.h"

#define NUEVA_CONEXION_NODO 1
#define NUEVA_CONEXION_YAMA 2
#define SOLICITAR_DATO 		3

char* PATH_CONFIG = "/home/utnso/Blacklist/tp-2017-2c-Blacklist/ProcesoFileSystem/src/config/config.txt";
Type_Config config;

char* PATH_LOG = "/home/utnso/Blacklist/Logs/logFileSystem.txt";
t_log* log_Console;
t_log* log_FileSystem;

bool ESTADO_ESTABLE;
bool CONNECT_DATANODE;

// Variables para el servidor
fd_set master;   	// conjunto maestro de descriptores de fichero

// Variables hilos
pthread_t thread_server;
pthread_t thread_consola;

void consola();
void init_log(char* pathLog);
void server(void* args);
void connection_handler(uint32_t socket, uint32_t command);

#endif /* FILESYSTEM_H_ */
