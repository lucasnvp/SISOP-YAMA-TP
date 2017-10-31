#ifndef YAMA_H_
#define YAMA_H_

#include <stdio.h>
#include <stdlib.h>

#include "commons/log.h"

#include "config/config_yama.h"

#include "commons/collections/list.h"

#define NUEVA_CONEXION_YAMA 2

#define NEW_JOB 1
#define NEW_JOB_STATUS 6

#define NEW_LOCAL_REDUCTION 3
#define NEW_LOCAL_REDUCTION_STATUS 7

#define NEW_GLOBAL_REDUCTION 4
#define NEW_GLOBAL_REDUCTION_STATUS 8

#define DATA_SAVING 5
#define DATA_SAVING_STATUS 9

typedef struct StatusTable {
	uint32_t JOB;
	uint32_t MASTER;
	uint32_t NODO;
	uint32_t BLOQUE;
	uint32_t ETAPA;
	char * ARCHIVO_TEMPORAL;
	uint32_t ESTADO; // Estado 1=En proceso 2=Error 3=Finalizado
} t_statusTable;



typedef struct nodoXDemanda {

	uint32_t NODO;
	uint32_t disponibilidad;
} t_nodoXDemanda;

t_list *listaNodoPorDemanda;

t_list *listaEstados;

t_list *listaNodosActivos;

char* PATH_CONFIG =
		"/home/utnso/Blacklist/tp-2017-2c-Blacklist/ProcesoYAMA/src/config/config.txt";
Type_Config config;

char* PATH_LOG = "/home/utnso/Blacklist/Logs/logYAMA.txt";
t_log* log_Console;
t_log* log_YAMA;

// Variables hilos
pthread_t thread_server;

char* DATOS_A_TRANSFORMAR;

uint32_t SERVIDOR_FILESYSTEM;

void connect_server_FileSystem();
void init_log(char* pathLog);
void server(void* args);
void connection_handler(uint32_t socket, uint32_t command);
uint32_t getNodoMenosOcupado();
uint32_t planificarTranformacion();
void solicitarBloquesAFS(char* ruta);
uint32_t A(int w);
uint32_t PWL(int w);
uint32_t WLmax();
uint32_t WL(int w);

#endif /* YAMA_H_ */
