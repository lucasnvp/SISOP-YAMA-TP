#include "setup.h"

void setup(char* RUTA_DATABIN, t_log* log_Console){
	if(access(RUTA_DATABIN, F_OK) != -1){
		data_setup(RUTA_DATABIN, log_Console);
	} else{
		log_warning(log_Console,"Error al leer el archivo BIN");
		exit(EXIT_SUCCESS);
	}
}

void data_setup(char* RUTA_DATABIN, t_log* log_Console){
	log_warning(log_Console,"Se leyo el archivo BIN");
}
