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

//	t_list * tablaEstado = list_create();
//	list_add(tablaEstado,"hola");
//	list_add(tablaEstado,"chau");
//	int  a= tablaEstado->elements_count;
//
//	int i=0;
//
//	for(i;i<a;i++)
//	{
//		printf("%s \n",list_get(tablaEstado,i));
//	}


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

void procesData()
{
	//lanzo hilo connection_handler a partir de la solicitud de un nuevo JOB de un MASTER X
}

	//ACLARACION: Conozco el estado de todos los MASTERS en el sistema, cada una de las operaciones que estos realizaron y deben realizazr
void connection_handler(uint32_t socket, uint32_t command){
	switch(command){
	case NEW_JOB:{ //NEW_TRANSFORMATION
		log_info(log_Console,"NEW JOB");
		DATOS_A_TRANSFORMAR = deserializar_string(socket);
		log_info(log_Console, "Dato a transformar: %s", DATOS_A_TRANSFORMAR);
		//1 Solicitar archivo al FS
		//2 Comunicarle a MASTER a que procesos WORKER debe conectarse con IP y PUERTO
		//3 Comunicarle a MASTER Sobre que WORKER debe aplicar el programa de transformacion
		//4 Comunicarle a MASTER El nombre de archivo temporal donde debera almacenar el resultado del script de Transformacion
		break;
	}
	case NEW_JOB_STATUS:{
		break;
	}
	case NEW_LOCAL_REDUCTION:{ //NEW_TRANSFORMATION
		//1 Comunicarle a MASTER nombre de los archivos temporales almacenados en cada uno de los nodos que debera procesar con el programa de reduccion
		//2 Comunicarle a MASTER nombre que le pondra a cada archivo de reduccion por worker (local)
		break;
		}
	case NEW_LOCAL_REDUCTION_STATUS:{
		break;
	}
	case NEW_GLOBAL_REDUCTION:{
		//1 Comunicarle a MASTER lista de nodos con ip y puerto de WORKER
		//2 Comunicarle a MASTER el nombre temporal de reduccion local de cada WORKER
		//3 Comunicarle a MASTER un WORKER Designado como encargado para Reduccion Global
		//4 Comunicarle a MASTER la ruta de donte guardar el archivo de Reduccion Global
		break;
		}
	case NEW_GLOBAL_REDUCTION_STATUS:{

		break;
		}
	case DATA_SAVING:{
		//1 Comunicarle a MASTER ip y puerto de WORKER a cual conectarse para guardar
		//1 El nombre del archivo para guardar en la ruta previamente indicada en la Reduccion global
		break;
		}
	case DATA_SAVING_STATUS:{
		break;
	}
	default:
		log_info(log_Console,"Error al recibir el comando");
	}

	return;
}
