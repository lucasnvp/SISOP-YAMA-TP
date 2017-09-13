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

int main(void) {
	puts("Proceso DataNode"); /* prints Proceso DataNode */

	//Inicializar Log
	init_log(PATH_LOG);

	//Configuracion inicial
	config = load_config(PATH_CONFIG);
	print_config(config, log_Console);

	//Conexion al servidor FileSystem
	connect_server_FileSystem();

	//Espera de solicitudes
	while(true){

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
		log_info(log_Console,"Connected successfully to the File System");
		// Le informo al FS que nodo es
		serializar_int(SERVIDOR_FILESYSTEM, NUEVA_CONEXION_NODO);
		// Retorno del estado del FS
		uint32_t estado_FS = deserializar_int(SERVIDOR_FILESYSTEM);
		if(estado_FS == true){
			serializar_string(SERVIDOR_FILESYSTEM,config.NOMBRE_NODO);
			log_info(log_Console,"File System Stable");
		} else{
			log_warning(log_Console,"File System ya formateado");
			exit(EXIT_SUCCESS);
		}
	} else{
		log_warning(log_Console, "No se puedo conectar al servidor de File System");
		exit(EXIT_SUCCESS);
	}
}
