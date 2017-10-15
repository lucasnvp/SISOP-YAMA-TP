#include "config_filesystem.h"

Type_Config load_config(char* path){
	Type_Config config;
	t_config *auxConfig;
	auxConfig = config_create(path);

	config.PUERTO_FILESYSTEM = config_get_int_value(auxConfig, "PUERTO_FILESYSTEM");
	config.CANTCONEXIONES = config_get_int_value(auxConfig, "CANTCONEXIONES");

	config_destroy(auxConfig);

	return config;
}

void print_config(Type_Config auxConfig, t_log* log_Console){
	log_info(log_Console, "---- Configuracion ----");
	log_info(log_Console, " PUERTO = %d",auxConfig.PUERTO_FILESYSTEM);
	log_info(log_Console, " CANTCONEXIONES = %d",auxConfig.CANTCONEXIONES);
	log_info(log_Console, "-----------------------");
}
