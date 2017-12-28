#ifndef ARCHIVOS_H_
#define ARCHIVOS_H_

#include "commons/log.h"
#include "commons/collections/list.h"

#include "../estructuras/structs.h"

t_log* log_Console;
t_log* log_FileSystem;

t_list * LIST_ARCHIVOS;

void setup_archivos(t_log* console, t_log* fileSystem);
void info_file(t_archivo* file);
t_archivo* new_file(uint32_t sizeFile, char* tipo, uint32_t dir_Padre, t_bloque* bloques);

#endif /* ARCHIVOS_H_ */
