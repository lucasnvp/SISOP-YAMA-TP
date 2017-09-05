#ifndef NODO_H_
#define NODO_H_

#include <stdio.h>
#include <stdlib.h>

#include "commons/log.h"

#include "config/config_nodo.h"

char* PATH_CONFIG = "/home/utnso/Blacklist/tp-2017-2c-Blacklist/ProcesoNodo/src/config/config.txt";
Type_Config config;

char* PATH_LOG = "/home/utnso/Blacklist/Logs/logNodo.txt";
t_log* log_Console;
t_log* log_Nodo;

void init_log(char* pathLog);

#endif /* NODO_H_ */