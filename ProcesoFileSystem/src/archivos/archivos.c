#include "archivos.h"

void setup_archivos(){
	LIST_ARCHIVOS = list_create();
}

t_archivo* new_file(uint32_t sizeFile, char* tipo, uint32_t dir_Padre, t_bloque* bloques){
	t_archivo* file = malloc(sizeof(t_archivo));
	file->tamanio = sizeFile;
	file->tipo = strdup(tipo);
	file->dir_padre = dir_Padre;
	file->estado = true;
	file->bloques = bloques;

	list_add(LIST_ARCHIVOS, file);

	return file;
}
