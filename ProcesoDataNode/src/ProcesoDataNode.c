/*
 ============================================================================
 Name        : ProcesoDataNode.c
 Author      : Blacklist
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "ProcesoDataNode.h"

int main(int argc, char *argv[]) {
	puts("Proceso DataNode"); /* prints Proceso DataNode */

	//Inicializar Log
	init_log(PATH_LOG);

	//Configuracion inicial
	PATH_CONFIG = strdup(argv[1]);
	config = load_config(PATH_CONFIG);
	print_config(config, log_Console);

	//Setup
	bin = setup(config.RUTA_DATABIN, log_Console);

	//Conexion al servidor FileSystem
	connect_server_FileSystem();

	//Espera de solicitudes
	while(true){
		uint32_t command = deserializar_int(SERVIDOR_FILESYSTEM);
		connection_handler(command);
	}

	return EXIT_SUCCESS;
}

void init_log(char* pathLog){
	mkdir("/home/utnso/Blacklist/Logs",0755);
	log_Console = log_create(pathLog, "DataNode", true, LOG_LEVEL_INFO);
	log_DataNode = log_create(pathLog, "DataNode", false, LOG_LEVEL_INFO);
}

void connect_server_FileSystem(){
    //Conexion al servidor FileSystem
	SERVIDOR_FILESYSTEM = connect_server(config.IP_FILESYSTEM,config.PUERTO_FILESYSTEM);

	//Si conecto, informo
	if(SERVIDOR_FILESYSTEM > 1){
		// Le informo al FS que nodo es
		serializar_int(SERVIDOR_FILESYSTEM, NUEVA_CONEXION_NODO);
		// Retorno del estado del FS
		uint32_t estado_FS = deserializar_int(SERVIDOR_FILESYSTEM);
		if(estado_FS == true){
			//Armar la estructura de nodo
			t_nodo* nodo = New_Nodo(config.NOMBRE_NODO, config.PUERTO_WORKER, bytesToMB(bin->size));
			//Serializar el nodo
			serializar_nodo(SERVIDOR_FILESYSTEM, nodo);
			//Free info enviadad
			free(nodo);

			log_info(log_Console,"Connected successfully to the File System");
		} else{
			log_warning(log_Console,"File System ya formateado");
			exit(EXIT_SUCCESS);
		}
	} else{
		log_warning(log_Console, "No se puedo conectar al servidor de File System");
		exit(EXIT_SUCCESS);
	}
}

void connection_handler(uint32_t command) {
	switch(command) {
	case GETBLOQUE: {
		//Deserializar el bloque a leer
		uint32_t bloqueALeer = deserializar_int(SERVIDOR_FILESYSTEM);
		//Leo el bloque
		char* bloque = getBloque(bloqueALeer);
		//Serializo el bloque
		serializar_string(SERVIDOR_FILESYSTEM, bloque);
		//Libero lo leido
		free(bloque);

		break;
	}
	case SETBLOQUE: {
		//Deserializar los datos
		//setBloque(uint32_t numero, char* datos);
		break;
	}
	default:
		log_info(log_Console, "Error al recibir el comando");
	}

	return;
}

void setBloque(uint32_t numero, char* datos){
	//Me ubico en que posicion tengo que escribir.
	uint32_t posicionBloque = numero * TAMANIO_FIJO_BLOQUE;

	//Poner un mutex por las dudas
	memcpy(bin->binmap + posicionBloque , datos, strlen(datos));
}

char* getBloque(uint32_t numero){

	uint32_t posicionBloque = numero * TAMANIO_FIJO_BLOQUE;

	char* bufferBloque = malloc(TAMANIO_FIJO_BLOQUE);

	memcpy(bufferBloque, bin->binmap + posicionBloque, TAMANIO_FIJO_BLOQUE);

	return bufferBloque;
}
