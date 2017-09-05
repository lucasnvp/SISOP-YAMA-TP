#include "config_nodo.h"

Type_Config load_config(char* path){
	Type_Config config;
	t_config *auxConfig;
	auxConfig = config_create(path);

	config.PUERTO_FILESYSTEM = config_get_int_value(auxConfig, "PUERTO_FILESYSTEM");
	config.IP_FILESYSTEM = strdup(config_get_string_value(auxConfig, "IP_FILESYSTEM"));
	config.NOMBRE_NODO = strdup(config_get_string_value(auxConfig, "NOMBRE_NODO"));
	config.PUERTO_WORKER = config_get_int_value(auxConfig, "PUERTO_WORKER");
	config.PUERTO_DATANODE = config_get_int_value(auxConfig, "PUERTO_DATANODE");
	config.RUTA_DATABIN = strdup(config_get_string_value(auxConfig, "RUTA_DATABIN"));

	config_destroy(auxConfig);

	return config;
}

void print_config(Type_Config auxConfig, t_log* log_Console){
	log_info(log_Console, "----------------------");
	log_info(log_Console, "Configuracion:");
	log_info(log_Console, "PUERTO = %d",auxConfig.PUERTO_FILESYSTEM);
	log_info(log_Console, "PUNTO_MONTAJE = %s",auxConfig.IP_FILESYSTEM);
	log_info(log_Console, "NOMBRE_NODO = %s",auxConfig.NOMBRE_NODO);
	log_info(log_Console, "PUERTO_WORKER = %d",auxConfig.PUERTO_WORKER);
	log_info(log_Console, "PUERTO_DATANODE = %d",auxConfig.PUERTO_DATANODE);
	log_info(log_Console, "RUTA_DATABIN = %s",auxConfig.RUTA_DATABIN);
	log_info(log_Console, "----------------------");
}
