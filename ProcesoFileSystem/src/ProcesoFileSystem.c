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

int main(void) {
	puts("Proceso FileSystem"); /* prints Proceso FileSystem */
	return EXIT_SUCCESS;
}

void init_log(char* pathLog){
	mkdir("/home/utnso/Blacklist/Logs",0755);
	log_Console = log_create(pathLog, "FileSystem", true, LOG_LEVEL_INFO);
	log_FileSystem = log_create(pathLog, "FileSystem", false, LOG_LEVEL_INFO);
}
