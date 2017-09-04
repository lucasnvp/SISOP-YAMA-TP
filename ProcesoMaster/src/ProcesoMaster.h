#ifndef MASTER_H_
#define MASTER_H_

#include <stdio.h>
#include <stdlib.h>

#include "commons/log.h"

char* PATH_LOG = "/home/utnso/Blacklist/Logs/logMaster.txt";
t_log* log_Console;
t_log* log_Master;

void init_log(char* pathLog);

#endif /* MASTER_H_ */
