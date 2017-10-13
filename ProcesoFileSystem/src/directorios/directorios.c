#include "directorios.h"

void setup_directorys(t_log* console, t_log* fileSystem){
	log_Console = console;
	log_FileSystem = fileSystem;

	if(ValidarArchivo((char*) PATH_DIRECTORIOS)){
		reload_directorys();
	} else{
		mkdir(PATH_METADATA, 0777);
		strcpy(directorios[0].nombre, "root");
		directorios[0].padre = -1;
	}
}

void remove_directory_yamafs(uint32_t index){
	uint32_t i;
	bool puedeEliminar = true;

	for(i = 0; i <= 99; i++){
		if(directorios[i].padre == index){
			puedeEliminar = false;
			log_info(log_FileSystem,"No se puede eliminar el directorio, no se encuentra vacio");
			break;
		}
	}

	if(puedeEliminar){
		strcpy(directorios[index].nombre, "");
		directorios[index].padre = 0;
		log_info(log_FileSystem,"Se ha elimiando el directorio");
	}
}

void listar_directorios(t_log* log_FileSystem){
	uint32_t i;
	log_info(log_FileSystem, "Index\tDirectorio\tPadre");
	for(i = 0; i <= 99; i++){
		if(!string_equals_ignore_case(directorios[i].nombre, "")){
			log_info(log_FileSystem, "%i\t%s\t%i", directorios[i].index, directorios[i].nombre, directorios[i].padre);
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
			string_append_with_format(&registros, "%s\t%s\t%s\n", string_itoa(directorios[i].index), directorios[i].nombre , string_itoa(directorios[i].padre));
			fwrite(registros,1,strlen(registros),directory);
			free(registros);
		}
	}

	//Cierro el archivo
	fclose(directory);
}

void new_directory_yamafs(char* directorio){
	uint32_t i = 0;
	int32_t padre = 0;
	int32_t cantArgs;
	int32_t beforLastArg;
	bool puedeGuargar = true;

	char** nameDir = string_split(directorio, "/");

	// Cuantos argumentos son
	cantArgs = cantidad_Argumentos(nameDir);

	// Valido los argumentos
	beforLastArg = cantArgs - 1;
	if(cantArgs !=0) padre = search_Index(nameDir, beforLastArg);
	if(padre == -1){
		log_info(log_FileSystem,"No se pudo crear el directorio");
		puedeGuargar = false;
	}

	// Valido que ya no este creado
	for(i = 1; i <= 99; i++){
		if(string_equals_ignore_case(directorios[i].nombre, nameDir[cantArgs]))
			if(directorios[i].padre == padre){
				log_info(log_FileSystem,"El directorio ya esta creado");
				puedeGuargar = false;
			}
	}

	// Guardo el ultimo argumento
	if(puedeGuargar){
		for(i = 1; i <= 99; i++){
			if(string_equals_ignore_case(directorios[i].nombre, "")){
				directorios[i].index = i;
				strcpy(directorios[i].nombre, nameDir[cantArgs]);
				directorios[i].padre = padre;
				break;
			}
		}
		log_info(log_FileSystem,"Directorio creado");
	}
}

void reload_directorys(){
	FILE * fileToRead = fopen(PATH_DIRECTORIOS,"r");

	char* datosLeidos = malloc(255);
	fgets(datosLeidos,255,fileToRead);

	while(fgets(datosLeidos,255,fileToRead)){
		char** dato = string_split(datosLeidos, "\t");
		directorios[atoi(dato[0])].index = atoi(dato[0]);
		strcpy(directorios[atoi(dato[0])].nombre, dato[1]);
		directorios[atoi(dato[0])].padre = atoi(dato[2]);
	}

	free(datosLeidos);
	fclose(fileToRead);
}

void rename_directory_yamafs(char* pathOriginal, char* nombreFinal){
	uint32_t i = 0;
	uint32_t index = 0;
	int32_t cantArgs;

	// Separo el path por cada "/" que tiene
	char** nameDir = string_split(pathOriginal, "/");

	// Cuantos argumentos son
	cantArgs = cantidad_Argumentos(nameDir);

	// Busco el padre del dir
	index = search_Index(nameDir, cantArgs);

	// Busco el directorio a renombrar
	if(index == -1){
		log_info(log_FileSystem,"Error al buscar el path");
	} else{
		strcpy(directorios[index].nombre, nombreFinal);
		log_info(log_FileSystem,"El directorio fue renombrado");
	}

}

void move_directory_yamafs(char* pathOriginal, char* pathFinal){
	bool puedeMover = true;
	// Separo los path  por cada "/" que tiene
	char** nameDirOriginal = string_split(pathOriginal, "/");
	char** nameDirFinal = string_split(pathFinal, "/");

	// Busco los index de ambos
	uint32_t indexOriginal = search_Index(nameDirOriginal, cantidad_Argumentos(nameDirOriginal));
	uint32_t indexFinal = search_Index(nameDirFinal, cantidad_Argumentos(nameDirFinal));

	if(indexOriginal == -1){
		log_info(log_FileSystem,"El directorio original no fue encontrado");
		puedeMover = false;
	}
	if(indexFinal == -1){
		log_info(log_FileSystem,"El directorio final no fue encontrado");
		puedeMover = false;
	}

	// Muevo el directorio
	if(puedeMover){
		directorios[indexOriginal].padre = directorios[indexFinal].index;
		log_info(log_FileSystem,"El directorio fue movido");
	}
}

int32_t cantidad_Argumentos(char** spitPath){
	uint32_t i = 0;
	int32_t cantArgs = -1;
	// Cuantos argumentos son
	while(spitPath[i] != NULL){
		cantArgs++;
		i++;
	}
	return cantArgs;
}

int32_t search_Index(char** splitPath, int32_t cantArgs){
	uint32_t i, j = 0;
	bool encontrado = false;
	int32_t index = 0;

	// Busco el padre del dir
	while(j <= cantArgs){
		for(i = 1; i <= 99; i++){
			if(string_equals_ignore_case(directorios[i].nombre, splitPath[j]))
				if(directorios[i].padre == index){
					index = directorios[i].index;
					encontrado = true;
				}
		}
		j++;
	}

	if(!encontrado){
//		log_info(log_FileSystem, "No se encontro el directorio");
		index = -1;
	}

	return index;
}

int32_t search_path_Index(char* path){
	char** splitPath = string_split(path, "/");
	uint32_t index = search_Index(splitPath, cantidad_Argumentos(splitPath));
	return index;
}
