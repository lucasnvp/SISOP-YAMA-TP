#ifndef MASTER_H_
#define MASTER_H_

#include <stdio.h>
#include <stdlib.h>

#include "commons/log.h"

#include "config/config_master.h"

#define CONEXION_A_YAMA 1
#define NEW_JOB 		1

char* PATH_CONFIG = "/home/utnso/Blacklist/tp-2017-2c-Blacklist/ProcesoMaster/src/config/config.txt";
Type_Config config;

char* PATH_LOG = "/home/utnso/Blacklist/Logs/logMaster.txt";
t_log* log_Console;
t_log* log_Master;

char* TRANSFORMADOR;
char* REDUCTOR;
char* DATOS_A_TRANSFORMAR;
char* RESULTADO_DE_LA_TRANSFORMACION;

uint32_t SERVIDOR_YAMA;

void connect_server_YAMA();
void init_log(char* pathLog);

#endif /* MASTER_H_ */
