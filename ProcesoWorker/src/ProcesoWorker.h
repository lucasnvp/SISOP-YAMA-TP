#ifndef WORKER_H_
#define WORKER_H_

#include <stdio.h>
#include <stdlib.h>

#include "commons/log.h"

#include "config/config_nodo.h"

char* PATH_CONFIG = "/home/utnso/Blacklist/tp-2017-2c-Blacklist/ProcesoWorker/src/config/config.txt";
Type_Config config;

char* PATH_LOG = "/home/utnso/Blacklist/Logs/logWorker.txt";
t_log* log_Console;
t_log* log_Worker;

// Variables hilos
pthread_t thread_server;

void init_log(char* pathLog);
void server(void* args);
void connection_handler(uint32_t socket, uint32_t command);

#endif /* WORKER_H_ */
