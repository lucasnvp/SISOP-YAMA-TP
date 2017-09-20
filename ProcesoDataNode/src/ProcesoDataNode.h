#ifndef DATANODE_H_
#define DATANODE_H_

#include <stdio.h>
#include <stdlib.h>

#include "commons/log.h"
#include "serializador/estructuras.h"

#include "config/config_nodo.h"
#include "setup/setup.h"

#define TAMANIO_FIJO_BLOQUE 1048576
#define NUEVA_CONEXION_NODO 1
#define GETBLOQUE			1
#define SETBLOQUE			2

char* PATH_CONFIG = "/home/utnso/Blacklist/tp-2017-2c-Blacklist/ProcesoDataNode/src/config/config.txt";
Type_Config config;

char* PATH_LOG = "/home/utnso/Blacklist/Logs/logDataNode.txt";
t_log* log_Console;
t_log* log_DataNode;

t_bin* bin;

uint32_t SERVIDOR_FILESYSTEM;

void connect_server_FileSystem();
void init_log(char* pathLog);
void connection_handler(uint32_t command);
void setBloque(uint32_t numero, char* datos);
char* getBloque(uint32_t numero);

#endif /* DATANODE_H_ */
