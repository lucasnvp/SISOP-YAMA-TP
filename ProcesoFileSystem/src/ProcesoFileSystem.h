#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "commons/log.h"
#include "commons/string.h"
#include "commons/collections/list.h"
#include "servidor/servidor.h"
#include "serializador/serializador.h"
#include "serializador/estructuras.h"

#include "config/config_filesystem.h"
#include "comandos/comandos.h"

#define NUEVA_CONEXION_NODO 1
#define NUEVA_CONEXION_YAMA 2
#define SOLICITAR_DATO 		3

static const char* clean = "--clean";

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

typedef struct {
	uint32_t cantArgs;
	char * comando;
	char * arg[4];
} t_comandos;

void consola();
void init_log(char* pathLog);
void server(void* args);
void connection_handler(uint32_t socket, uint32_t command);

#endif /* FILESYSTEM_H_ */
