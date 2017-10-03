#ifndef DIRECTORYS_H_
#define DIRECTORYS_H_

#include <stdio.h>

#include "commons/log.h"
#include "commons/string.h"

#include "../estructuras/structs.h"

struct Directorio directorios[99];

static const char* PATH_METADATA = "/home/utnso/Blacklist/metadata/";
static const char* PATH_DIRECTORIOS = "/home/utnso/Blacklist/metadata/directorios.dat";

t_log* log_Console;
t_log* log_FileSystem;

void setup_directorys(t_log* console, t_log* fileSystem);
void reload_directorys();
void persistir_directorios();
int32_t cantidad_Argumentos(char** spitPath);
int32_t search_Index(char** splitPath, int32_t cantArgs);

void new_directory_yamafs(char* directorio);
void rename_directory_yamafs(char* pathOriginal, char* nombreFinal);
void remove_directory_yamafs(uint32_t index);
void move_directory_yamafs(char* pathOriginal, char* pathFinal);
void listar_directorios(t_log* log_FileSystem);

#endif /* DIRECTORYS_H_ */
