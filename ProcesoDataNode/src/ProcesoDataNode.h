#ifndef DATANODE_H_
#define DATANODE_H_

#include <stdio.h>
#include <stdlib.h>

#include "commons/log.h"

#include "config/config_nodo.h"

char* PATH_CONFIG = "/home/utnso/Blacklist/tp-2017-2c-Blacklist/ProcesoDataNode/src/config/config.txt";
Type_Config config;

char* PATH_LOG = "/home/utnso/Blacklist/Logs/logDataNode.txt";
t_log* log_Console;
t_log* log_DataNode;

void init_log(char* pathLog);

#endif /* DATANODE_H_ */
