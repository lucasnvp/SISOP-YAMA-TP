#include "config_yama.h"

Type_Config load_config(char* path){
	Type_Config config;
	t_config *auxConfig;
	auxConfig = config_create(path);

	config.FS_PUERTO = config_get_int_value(auxConfig, "FS_PUERTO");
	config.FS_IP = strdup(config_get_string_value(auxConfig, "FS_IP"));
	config.RETARDO_PLANIFICACION = config_get_int_value(auxConfig, "RETARDO_PLANIFICACION");
	config.ALGORITMO_BALANCEO = strdup(config_get_string_value(auxConfig, "ALGORITMO_BALANCEO"));

	config_destroy(auxConfig);

	return config;
}

void print_config(Type_Config auxConfig, t_log* log_Console){
	log_info(log_Console, "----------------------");
	log_info(log_Console, "Configuracion:");
	log_info(log_Console, "PUERTO = %d",auxConfig.FS_PUERTO);
	log_info(log_Console, "PUNTO_MONTAJE = %s",auxConfig.FS_IP);
	log_info(log_Console, "RETARDO_PLANIFICACION = %d",auxConfig.RETARDO_PLANIFICACION);
	log_info(log_Console, "ALGORITMO_BALANCEO = %s",auxConfig.ALGORITMO_BALANCEO);
	log_info(log_Console, "----------------------");
}
