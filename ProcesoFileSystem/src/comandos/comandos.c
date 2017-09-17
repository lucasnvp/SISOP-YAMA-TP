#include "comandos.h"

void print_console(void (*log_function)(t_log*, const char*), char* message) {
	log_function(log_FileSystem, message);
	printf("%s", message);
}

bool format(){
	return true;
}
