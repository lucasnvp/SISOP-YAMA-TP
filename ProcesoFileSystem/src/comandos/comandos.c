#include "comandos.h"

void print_console(void (*log_function)(t_log*, const char*), char* message) {
	log_function(log_FileSystem, message);
	printf("%s", message);
}

void format(bool ESTADO_ESTABLE, bool CONNECT_DATANODE){
	sizeFS();

	//Persisto los nodos
	persistir_nodos();

	ESTADO_ESTABLE = true;
	CONNECT_DATANODE = false;
	print_console((void*) log_info, "File System formateado.");
}

void exitToTheFS(){
	//Cierro la conexion con todos los nodos
	close_nodes_conexions();

	//Persisto los directorios
	persistir_directorios();
}

void copyFromFStoYamafs(char* pathFS, char* dirYamafs){
	if(ValidarArchivo(pathFS)){
		FILE * file;
		uint32_t cantBloques = 0;
		char* datosLeidos = malloc(TAMANIO_FIJO_BLOQUE);

		//Abro el archivo
		file = fopen(pathFS, "r");

		// Size del archivo
		fseek(file, 0L, SEEK_END);
		uint32_t sizeFile = ftell(file);
		rewind(file);
		printf("Tamanio del archivo a copiar: %i \n", sizeFile);

		// Cantidad de bloques necesarios para el archivo
		cantBloques = 1 + ( (sizeFile - 1) / TAMANIO_FIJO_BLOQUE);
		t_list* listadoDeBloques = reservar_bloques(cantBloques);

		while(fgets(datosLeidos, TAMANIO_FIJO_BLOQUE, file)){
			printf("%s", datosLeidos);
			//Enviar los datos a los bloques //
		}

		free(datosLeidos);
		fclose(file);

	} else{
		log_warning(log_FileSystem, "No se encontro el archivo");
	}
}

t_archivo* newFileInYamafs(char* path, char* pathYamafs){
	if(ValidarArchivo(path)){
		if(search_path_Index(pathYamafs) != -1){
			t_archivo* newFile = new_file(sizeArchivo(path),typeArchivo(path),search_path_Index(pathYamafs),NULL);
			info_file(newFile);
			return newFile;
		} else {
			log_warning(log_FileSystem, "No se encontro el path el YamaFS");
		}
	} else{
		log_warning(log_FileSystem, "No se encontro el archivo");
	}
}
