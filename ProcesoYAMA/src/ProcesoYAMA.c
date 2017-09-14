/*
 ============================================================================
 Name        : ProcesoYAMA.c
 Author      : Blacklist
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "ProcesoYAMA.h"

int main(void) {
	puts("Proceso YAMA"); /* prints Proceso YAMA */

	//Inicializar Log
	init_log(PATH_LOG);

	//Configuracion inicial
	config = load_config(PATH_CONFIG);
	print_config(config, log_Console);

	//Conexion al servidor FileSystem
	connect_server_FileSystem();

	//Creo el hilo del servidor
	pthread_create(&thread_server,NULL,(void*) server,"Servidor");

	pthread_join(thread_server, (void**) NULL);

	return EXIT_SUCCESS;
}

void init_log(char* pathLog){
	mkdir("/home/utnso/Blacklist/Logs",0755);
	log_Console = log_create(pathLog, "YAMA", true, LOG_LEVEL_INFO);
	log_YAMA = log_create(pathLog, "YAMA", false, LOG_LEVEL_INFO);
}

void connect_server_FileSystem(){
    //Conexion al servidor FileSystem
	SERVIDOR_FILESYSTEM = connect_server(config.FS_IP,config.FS_PUERTO);

	//Si conecto, informo
	if(SERVIDOR_FILESYSTEM > 1){
		log_info(log_Console,"Connected successfully to the File System");
		// Le informo al FS que es una conexion YAMA
		serializar_int(SERVIDOR_FILESYSTEM, NUEVA_CONEXION_YAMA);
		// Retorno del estado del FS
		uint32_t estado_FS = deserializar_int(SERVIDOR_FILESYSTEM);
		if(estado_FS == true){
			log_info(log_Console,"File System Stable");
		} else{
			log_warning(log_Console,"File System Unstable");
			exit(EXIT_SUCCESS);
		}
	} else{
		log_warning(log_Console, "No se puedo conectar al servidor de File System");
		exit(EXIT_SUCCESS);
	}
}

void server(void* args){
	// Variables para el servidor
	fd_set master;   	// conjunto maestro de descriptores de fichero
	fd_set read_fds; 	// conjunto temporal de descriptores de fichero para select()
	uint32_t fdmax;			// número máximo de descriptores de fichero
	int i;				// variable para el for
	FD_ZERO(&master);	// borra los conjuntos maestro
	FD_ZERO(&read_fds);	// borra los conjuntos temporal

	//Creacion del servidor
	uint32_t SERVIDOR_YAMA = build_server(config.YAMA_PUERTO, config.CANTCONEXIONES);

	//El socket esta listo para escuchar
	if(SERVIDOR_YAMA > 0){
		log_info(log_Console,"Servidor YAMA Escuchando");
	}

	// añadir listener al conjunto maestro
	FD_SET(SERVIDOR_YAMA, &master);

	// seguir la pista del descriptor de fichero mayor
	fdmax = SERVIDOR_YAMA; // por ahora es éste

	// bucle principal
	while(true) {
		read_fds = master; // cópialo
		if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
			perror("select");
			exit(1);
		}
		// explorar conexiones existentes en busca de datos que leer
		for(i = 0; i <= fdmax; i++) {
			if (FD_ISSET(i, &read_fds)) { // ¡¡tenemos datos!!
				if (i == SERVIDOR_YAMA) {
					// acepto una nueva conexion
					uint32_t newfd = accept_conexion(SERVIDOR_YAMA);
					FD_SET(newfd, &master); // añadir al conjunto maestro
					if (newfd > fdmax) {    // actualizar el máximo
						fdmax = newfd;
					}
				} else {
					//Recibo el comando
					uint32_t command = deserializar_int(i);

					// gestionar datos de un cliente
					if(command <= 0){
						close(i); // Close conexion
						FD_CLR(i, &master); // eliminar del conjunto maestro
					}else {
						connection_handler(i, command);
					}
				}
			}
		}
	}
}

void connection_handler(uint32_t socket, uint32_t command){
	switch(command){
	case NEW_JOB:{
		log_info(log_Console,"NEW JOB");
		DATOS_A_TRANSFORMAR = deserializar_string(socket);
		log_info(log_Console, "Dato a transformar: %s", DATOS_A_TRANSFORMAR);
		//Solicitar dato al FS
		break;
	}
	default:
		log_info(log_Console,"Error al recibir el comando");
	}

	return;
}
