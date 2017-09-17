#ifndef SETUP_H_
#define SETUP_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/stat.h>

#include "commons/log.h"

void setup(char* RUTA_DATABIN, t_log* log_Console);
void data_setup(char* RUTA_DATABIN, t_log* log_Console);

#endif /* SETUP_H_ */
