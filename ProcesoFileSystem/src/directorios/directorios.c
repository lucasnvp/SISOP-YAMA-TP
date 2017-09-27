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

void persistir_directorios(){
	//Abro el archivo en modo escritura
	FILE* directory = fopen(PATH_DIRECTORIOS, "w+b");

	//Encabezado
	char* encabezado = string_new();
	string_append_with_format(&encabezado, "Index\tDirectorio\tPadre\n");
	fwrite(encabezado,1,strlen(encabezado),directory);
	free(encabezado);

	uint32_t i;
	for(i = 1; i <= 99; i++){
		char* registros = string_new();
		string_append_with_format(&registros, "%s\t%s\t%s\n", string_itoa(i), directorios[i].nombre , string_itoa(directorios[i].padre));
		fwrite(registros,1,strlen(registros),directory);
		free(registros);
	}

	//Cierro el archivo
	fclose(directory);
}

void new_directory_yamafs(char* directorio, uint32_t padre){
	uint32_t i;
	for(i = 1; i <= 99; i++){
		if(string_equals_ignore_case(directorios[i].nombre, "")){
			strcpy(directorios[i].nombre, directorio);
			directorios[i].padre = padre;
			break;
		}
	}
}
