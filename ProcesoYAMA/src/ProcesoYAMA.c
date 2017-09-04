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
	return EXIT_SUCCESS;
}

void init_log(char* pathLog){
	mkdir("/home/utnso/Blacklist/Logs",0755);
	log_Console = log_create(pathLog, "YAMA", true, LOG_LEVEL_INFO);
	log_YAMA = log_create(pathLog, "YAMA", false, LOG_LEVEL_INFO);
}
