#ifndef COMANDOS_H_
#define COMANDOS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "commons/log.h"

t_log* log_FileSystem;

void print_console(void (*log_function)(t_log*, const char*), char* message);
void format(bool ESTADO_ESTABLE, bool CONNECT_DATANODE);
void exitToTheFS();

#endif /* COMANDOS_H_ */
