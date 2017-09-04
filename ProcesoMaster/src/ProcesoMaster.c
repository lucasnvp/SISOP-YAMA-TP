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

int main(void) {
	puts("Proceso Master"); /* prints Proceso Master */
	return EXIT_SUCCESS;
}

void init_log(char* pathLog){
	mkdir("/home/utnso/Blacklist/Logs",0755);
	log_Console = log_create(pathLog, "Master", true, LOG_LEVEL_INFO);
	log_Master = log_create(pathLog, "Master", false, LOG_LEVEL_INFO);
}
