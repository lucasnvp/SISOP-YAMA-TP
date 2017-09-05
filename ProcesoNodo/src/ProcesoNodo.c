/*
 ============================================================================
 Name        : ProcesoNodo.c
 Author      : Blacklist
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "ProcesoNodo.h"

int main(void) {
	puts("Proceso Nodo"); /* prints Proceso Nodo */

	//Inicializar Log
	init_log(PATH_LOG);

	//Configuracion inicial
	config = load_config(PATH_CONFIG);
	print_config(config, log_Console);

	return EXIT_SUCCESS;
}

void init_log(char* pathLog){
	mkdir("/home/utnso/Blacklist/Logs",0755);
	log_Console = log_create(pathLog, "Nodo", true, LOG_LEVEL_INFO);
	log_Nodo = log_create(pathLog, "Nodo", false, LOG_LEVEL_INFO);
}
