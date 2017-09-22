#include "comandos.h"

void print_console(void (*log_function)(t_log*, const char*), char* message) {
	log_function(log_FileSystem, message);
	printf("%s", message);
}

void format(bool ESTADO_ESTABLE, bool CONNECT_DATANODE){
	sizeFS();
	ESTADO_ESTABLE = true;
	CONNECT_DATANODE = false;
	print_console(log_info, "File System formateado.");
}

void exitToTheFS(){
	//Cierro la conexion con todos los nodos
	close_nodes_conexions();

	//Cierro el proceso
	exit(EXIT_SUCCESS);
}
