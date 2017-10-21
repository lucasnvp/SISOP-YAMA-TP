#include "archivos.h"

void setup_archivos(t_log* console, t_log* fileSystem){
	log_Console = console;
	log_FileSystem = fileSystem;

	LIST_ARCHIVOS = list_create();
}

t_archivo* new_file(uint32_t sizeFile, char* tipo, uint32_t dir_Padre, t_bloque* bloques){
	t_archivo* file = malloc(sizeof(t_archivo));
//	file->nombre = strdup();
	file->tamanio = sizeFile;
	file->tipo = strdup(tipo);
	file->dir_padre = dir_Padre;
	file->estado = true;
	file->bloques = bloques;

	list_add(LIST_ARCHIVOS, file);

	return file;
}

void info_file(t_archivo* file){
	log_info(log_FileSystem, "File size: %i", file->tamanio);
	log_info(log_FileSystem, "File type: %s", file->tipo);
	log_info(log_FileSystem, "File dir: %i", file->dir_padre);
	if (file->estado == true){
		log_info(log_FileSystem, "File status: Disponible");
	} else{
		log_info(log_FileSystem, "File status: No Disponible");
	}
}
