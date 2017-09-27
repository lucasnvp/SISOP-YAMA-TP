#include "directorios.h"

void setup_directorys(){
	if(ValidarArchivo(PATH_DIRECTORIOS)){
		//todo: Levantar la config de los directorios
		reload_directorys();
	} else{
		mkdir(PATH_METADATA, 0777);
		strcpy(directorios[0].nombre, "root");
		directorios[0].padre = -1;
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
		if(!string_equals_ignore_case(directorios[i].nombre, "")){
			log_info(log_FileSystem, "%i\t%s\t%i", i, directorios[i].nombre, directorios[i].padre);
		}
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
	for(i = 0; i <= 99; i++){
		if(!string_equals_ignore_case(directorios[i].nombre, "")){
			char* registros = string_new();
			string_append_with_format(&registros, "%s\t%s\t%s\n", string_itoa(i), directorios[i].nombre , string_itoa(directorios[i].padre));
			fwrite(registros,1,strlen(registros),directory);
			free(registros);
		}
	}

	//Cierro el archivo
	fclose(directory);
}

void new_directory_yamafs(char* directorio){
	uint32_t i;
	uint32_t padre = 0;

	char** nameDir = string_split(directorio, "/");

	for(i = 1; i <= 99; i++){
		if(string_equals_ignore_case(directorios[i].nombre, "")){
			strcpy(directorios[i].nombre, nameDir[0]);
			directorios[i].padre = padre;
			break;
		}
	}
}

void reload_directorys(){
	FILE * fileToRead = fopen(PATH_DIRECTORIOS,"r");
	uint32_t i = 0;

	char* datosLeidos = malloc(25);
	fgets(datosLeidos,25,fileToRead);

	while(fgets(datosLeidos,25,fileToRead)){
		char** dato = string_split(datosLeidos, "\t");
		directorios[i].index = 0;
		strcpy(directorios[i].nombre, dato[1]);
		directorios[i].padre = atoi(dato[2]);
		i++;
	}

	fclose(fileToRead);
}
