#ifndef COMANDOS_H_
#define COMANDOS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

#include "commons/log.h"
#include "commons/collections/list.h"
#include "commonsfunctions/fuctions.h"

#include "../estructuras/structs.h"

#define TAMANIO_FIJO_BLOQUE 1048576

t_log* log_FileSystem;

void print_console(void (*log_function)(t_log*, const char*), char* message);
void format(bool ESTADO_ESTABLE, bool CONNECT_DATANODE);
void exitToTheFS();
void copyFromFStoYamafs(char* pathFS, char* dirYamafs);
t_archivo* newFileInYamafs(char* path, char* pathYamafs);

#endif /* COMANDOS_H_ */
