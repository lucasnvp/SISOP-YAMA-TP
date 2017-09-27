#include "directorios.h"

void setup_directorys(){
	if(ValidarArchivo(PATH_DIRECTORIOS)){
		//todo: Levantar la config de los directorios
	} else{
		mkdir(PATH_METADATA, 0777);
		strcpy(directorios[0].nombre, "root");
		directorios[0].padre = -1;
		uint32_t i;
		for(i = 1; i <= 99; i++){
			remove_directory_yamafs(i);
		}
	}
}

void remove_directory_yamafs(uint32_t index){
	strcpy(directorios[index].nombre, "");
	directorios[index].padre = 0;
}

void listar_directorios(t_log* log_FileSystem){
	uint32_t i;
	log_info(log_FileSystem, "Index\tDirectorio\tPadre");
	for(i = 0; i <= 99; i++){
		log_info(log_FileSystem, "%i\t%s\t%i", i, directorios[i].nombre, directorios[i].padre);
	}
}
