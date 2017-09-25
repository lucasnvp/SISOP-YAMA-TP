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
	print_console(log_info, "File System formateado.");
}

void exitToTheFS(){
	//Cierro la conexion con todos los nodos
	close_nodes_conexions();

	//Cierro el proceso
	exit(EXIT_SUCCESS);
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
		printf("\n Cant de Bloques: %i \n", cantBloques);

		// Preguntar si tengo la cantidad de espacios necesarios en los nodos //

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
