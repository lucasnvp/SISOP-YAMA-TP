/*
 ============================================================================
 Name        : ProcesoMaster.c
 Author      : Blacklist
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "ProcesoMaster.h"

int main(int argc, char *argv[]) {
	puts("Proceso Master"); /* prints Proceso Master */

	//Inicializar Log
	init_log(PATH_LOG);

	//Configuracion inicial
	config = load_config(PATH_CONFIG);
	print_config(config, log_Console);

	//Conexion al servidor FileSystem
	connect_server_YAMA();

	//Cargo los argumentos
	TRANSFORMADOR = strdup(argv[1]);
	log_info(log_Console,"Archivo transformador: %s", argv[1]);
	REDUCTOR = strdup(argv[2]);
	log_info(log_Console,"Archivo reductor: %s", argv[2]);
	DATOS_A_TRANSFORMAR = strdup(argv[3]);
	log_info(log_Console,"Dato a transformar: %s", argv[3]);
	RESULTADO_DE_LA_TRANSFORMACION = strdup(argv[4]);
	log_info(log_Console,"Resultado: %s", argv[4]);

	// Envio el dato a transformar a YAMA
	serializar_string(SERVIDOR_YAMA, DATOS_A_TRANSFORMAR);

	//Lo que tiene que hacer!
	while(true){

	}

	return EXIT_SUCCESS;
}

void init_log(char* pathLog){
	mkdir("/home/utnso/Blacklist/Logs",0755);
	log_Console = log_create(pathLog, "Master", true, LOG_LEVEL_INFO);
	log_Master = log_create(pathLog, "Master", false, LOG_LEVEL_INFO);
}

void connect_server_YAMA(){
    //Conexion al servidor FileSystem
	SERVIDOR_YAMA = connect_server(config.YAMA_IP,config.YAMA_PUERTO);

	//Si conecto, informo
	if(SERVIDOR_YAMA > 1){
		log_info(log_Console,"Connected successfully to the File System");
		// Le informo al FS que nodo es
		serializar_int(SERVIDOR_YAMA, CONEXION_A_YAMA);
	} else{
		log_warning(log_Console, "No se puedo conectar al servidor de File System");
		exit(EXIT_SUCCESS);
	}
}
