#ifndef YAMA_H_
#define YAMA_H_

#include <stdio.h>
#include <stdlib.h>

#include "commons/log.h"

char* PATH_LOG = "/home/utnso/Blacklist/Logs/logYAMA.txt";
t_log* log_Console;
t_log* log_YAMA;

void init_log(char* pathLog);

#endif /* YAMA_H_ */
