/*
 ============================================================================
 Name        : ProcesoWorker.c
 Author      : Blacklist
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "ProcesoWorker.h"

int main(void) {
	puts("Proceso Worker"); /* prints Proceso Worker */

	//Inicializar Log
	init_log(PATH_LOG);

	//Configuracion inicial
	config = load_config(PATH_CONFIG);
	print_config(config, log_Console);

	//Creo el hilo del servidor
	pthread_create(&thread_server,NULL,(void*) server,"Servidor");

	pthread_join(thread_server, (void**) NULL);

	return EXIT_SUCCESS;
}

void init_log(char* pathLog){
	mkdir("/home/utnso/Blacklist/Logs",0755);
	log_Console = log_create(pathLog, "Worker", true, LOG_LEVEL_INFO);
	log_Worker = log_create(pathLog, "Worker", false, LOG_LEVEL_INFO);
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
	uint32_t SERVIDOR_WORKER = build_server(config.PUERTO_WORKER, config.CANTCONEXIONES);

	//El socket esta listo para escuchar
	if(SERVIDOR_WORKER > 0){
		printf("Servidor WORKER Escuchando\n");
	}

	// añadir listener al conjunto maestro
	FD_SET(SERVIDOR_WORKER, &master);

	// seguir la pista del descriptor de fichero mayor
	fdmax = SERVIDOR_WORKER; // por ahora es éste

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
				if (i == SERVIDOR_WORKER) {
					// acepto una nueva conexion
					uint32_t newfd = accept_conexion(SERVIDOR_WORKER);
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
	case 1:{
		log_info(log_Console,"Primer connection handler");
		break;
	}
	default:
		log_info(log_Console,"Error al recibir el comando");
	}

	return;
}
