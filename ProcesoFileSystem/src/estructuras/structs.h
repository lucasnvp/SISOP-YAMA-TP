#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <stdio.h>
#include <inttypes.h>

#include "commons/collections/list.h"

typedef struct ArchivoBloques{
	uint32_t nroBloque;
	char* C1_Nodo;
	uint32_t C1_Bloque;
	char* C2_Nodo;
	uint32_t C2_Bloque;
	uint32_t finBloque;
}t_bloque;

typedef struct Archivo{
	uint32_t tamanio;
	char* tipo;
	uint32_t dir_padre;
	bool estado;
	t_list* bloques;
}t_archivo;

typedef struct Directorio{
	int32_t index;
	char nombre[255];
	int32_t padre;
}t_directory;

#endif /* STRUCTS_H_ */
