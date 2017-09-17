/*
 ============================================================================
 Name        : ProcesoFileSystem.c
 Author      : Blacklist
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "ProcesoFileSystem.h"

int main(int argc, char *argv[]) {
	system("clear"); /* limpia la pantalla al empezar */

	puts("Proceso FileSystem\n"); /* prints Proceso FileSystem */

	//Inicializar Log
	init_log(PATH_LOG);

	//Configuracion inicial
	config = load_config(PATH_CONFIG);
	print_config(config, log_Console);

	//El FS arranca como no estaba
	ESTADO_ESTABLE = false;
	CONNECT_DATANODE = true;

	//Compruebo el flag de clean
	if(argc > 1){
		if(!strcmp(argv[1], "--clean")){
			//Desarrollar el clean
		}
	}

	//Creo el hilo del servidor
	pthread_create(&thread_server, NULL, (void*) server, "Servidor");

	//Creo el hilo de la consola
	pthread_create(&thread_consola, NULL, (void*) consola, NULL);

	//pthread_join(thread_server, (void**) NULL);
	pthread_join(thread_consola, (void**) NULL);

	return EXIT_SUCCESS;
}

void consola() {
	char * com;
	char * linea;
	t_comandos * comandos;

	while (true) {
		comandos = (t_comandos *) malloc (sizeof(t_comandos));
		linea = readline("\nFile_System> ");

		if (strlen(linea) > 0) {
			log_info(log_FileSystem, "Linea: %s", linea);
			add_history(linea);

			com = strtok(linea, " ");
			comandos->comando = (char *) malloc (sizeof(char) * strlen(com));
			strcpy(comandos->comando, com);
			comandos->cantArgs = 0;

			com = strtok(NULL, " ");
			uint32_t i = 0;
			while (i < 4 && com) {
				comandos->arg[i] = (char *) malloc (sizeof(char) * strlen(com));
				strcpy(comandos->arg[i], com);
				comandos->cantArgs++;
				com = strtok(NULL, " ");
				i++;
			}
			free(com);

			if (!strcmp(comandos->comando, "exit")) {
				if (comandos->cantArgs == 0) {
					free(comandos->comando);
					free(comandos);
					free(linea);
					break;
				}
				else print_console(log_error, "Número de parámetros incorrecto.");
			}
			else if (!strcmp(comandos->comando, "format")) {
				if (comandos->cantArgs == 0) {
					if (format()) {
						ESTADO_ESTABLE = true;
						CONNECT_DATANODE = false;
						print_console(log_info, "File System formateado.");
					}
				}
				else print_console(log_error, "Número de parámetros incorrecto.");
			}
			else print_console(log_error, "Comando incorrecto.");

			// Libero toda la memoria
			for (i = 0; i < comandos->cantArgs; i++)
				free(comandos->arg[i]);

			free(comandos->comando);
		}
		free(comandos);
		free(linea);
	}
}

void init_log(char* pathLog) {
	mkdir("/home/utnso/Blacklist/Logs", 0755);
	log_Console = log_create(pathLog, "FileSystem", true, LOG_LEVEL_INFO);
	log_FileSystem = log_create(pathLog, "FileSystem", false, LOG_LEVEL_INFO);
}

void server(void* args) {
	fd_set read_fds; 	// conjunto temporal de descriptores de fichero para select()
	uint32_t fdmax;			// número máximo de descriptores de fichero
	int i;				// variable para el for
	FD_ZERO(&master);	// borra los conjuntos maestro
	FD_ZERO(&read_fds);	// borra los conjuntos temporal

	//Creacion del servidor
	uint32_t SERVIDOR_FILESYSTEM = build_server(config.PUERTO_FILESYSTEM, config.CANTCONEXIONES);

	//El socket esta listo para escuchar
	if(SERVIDOR_FILESYSTEM > 0) {
		log_info(log_FileSystem, "Servidor FileSystem Escuchando");
	}

	// añadir listener al conjunto maestro
	FD_SET(SERVIDOR_FILESYSTEM, &master);

	// seguir la pista del descriptor de fichero mayor
	fdmax = SERVIDOR_FILESYSTEM; // por ahora es éste

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
				if (i == SERVIDOR_FILESYSTEM) {
					// acepto una nueva conexion
					uint32_t newfd = accept_conexion(SERVIDOR_FILESYSTEM);
					FD_SET(newfd, &master); // añadir al conjunto maestro
					if (newfd > fdmax) {    // actualizar el máximo
						fdmax = newfd;
					}
				} else {
					//Recibo el comando
					uint32_t command = deserializar_int(i);

					// gestionar datos de un cliente
					if(command <= 0) {
						close(i); // Close conexion
						FD_CLR(i, &master); // eliminar del conjunto maestro
					} else {
						connection_handler(i, command);
					}
				}
			}
		}
	}
}

void connection_handler(uint32_t socket, uint32_t command) {
	switch(command) {
	case NUEVA_CONEXION_NODO: {
		//Se conecto un nodo
		if(CONNECT_DATANODE == true) {
			serializar_int(socket, true);
			char* nodo = deserializar_string(socket);
			log_info(log_FileSystem, "Se conecto el %s", nodo);
		} else {
			serializar_int(socket, false);
			close(socket);
			FD_CLR(socket, &master);
			log_warning(log_FileSystem, "Se rechazo la conexion de un NODO. El FileSystem ya se encuentra formateado");
		}
		break;
	}
	case NUEVA_CONEXION_YAMA: {
		//Se conecto YAMA
		if (ESTADO_ESTABLE == true) {
			log_info(log_FileSystem, "Se conecto YAMA");
			serializar_int(socket, true);
		} else {
			serializar_int(socket, false);
			close(socket);
			FD_CLR(socket, &master);
			log_warning(log_FileSystem, "No se pudo conectar YAMA por estado inestable");
		}
		break;
	}
	case SOLICITAR_DATO:{
		// Recibir el datos solicitado
		// Comprabar que existar
		// Devolver la lista de los NODOS que contienen los datos
		break;
	}
	default:
		log_info(log_FileSystem, "Error al recibir el comando");
	}

	return;
}
