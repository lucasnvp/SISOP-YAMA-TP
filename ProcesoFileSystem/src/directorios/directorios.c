#include "directorios.h"

void setup_directorys(t_log* console, t_log* fileSystem){
	log_Console = console;
	log_FileSystem = fileSystem;

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
	uint32_t i = 0;
	uint32_t padre = 0;
	int32_t cantArgs = -1;
	bool puedeGuargar = true;

	char** nameDir = string_split(directorio, "/");

	// Cuantos argumentos son
	while(nameDir[i] != NULL){
		cantArgs++;
		i++;
	}
//	log_info(log_FileSystem, "La cantidad de argumentos son: %i", cantArgs);

	// Valido los argumentos
	uint32_t j = 0;
	while(j < cantArgs){
		puedeGuargar = false;
		for(i = 1; i <= 99; i++){
			if(string_equals_ignore_case(directorios[i].nombre, nameDir[j])){
				padre = directorios[i].index;
				puedeGuargar = true;
//				log_info(log_FileSystem,"Argumento Encontrado");
			}
		}
		if(puedeGuargar == false){
			log_info(log_FileSystem,"No se pudo crear el directorio");
			break;
		}
		j++;
	}

	// Valido que ya no este creado
	for(i = 1; i <= 99; i++){

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
