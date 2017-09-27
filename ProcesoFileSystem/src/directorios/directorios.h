#ifndef DIRECTORYS_H_
#define DIRECTORYS_H_

#include <stdio.h>

#include "commons/log.h"
#include "commons/string.h"

#include "../estructuras/structs.h"

struct Directorio directorios[99];

static const char* PATH_METADATA = "/home/utnso/Blacklist/metadata/";
static const char* PATH_DIRECTORIOS = "/home/utnso/Blacklist/metadata/directorios.dat";

void setup_directorys();
void remove_directory_yamafs(uint32_t index);
void listar_directorios(t_log* log_FileSystem);
void persistir_directorios();
void new_directory_yamafs(char* directorio);
void reload_directorys();

#endif /* DIRECTORYS_H_ */
