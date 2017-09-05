#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include <stdio.h>
#include <stdlib.h>

#include "commons/log.h"

#include "config/config_filesystem.h"

char* PATH_CONFIG = "/home/utnso/Blacklist/tp-2017-2c-Blacklist/ProcesoFileSystem/src/config/config.txt";
Type_Config config;

char* PATH_LOG = "/home/utnso/Blacklist/Logs/logFileSystem.txt";
t_log* log_Console;
t_log* log_FileSystem;

void init_log(char* pathLog);

#endif /* FILESYSTEM_H_ */
