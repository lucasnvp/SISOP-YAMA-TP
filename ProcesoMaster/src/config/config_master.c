#include "config_master.h"

Type_Config load_config(char* path){
	Type_Config config;
	t_config *auxConfig;
	auxConfig = config_create(path);

	config.YAMA_PUERTO = config_get_int_value(auxConfig, "YAMA_PUERTO");

	config.YAMA_IP = strdup(config_get_string_value(auxConfig, "YAMA_IP"));

	config_destroy(auxConfig);

	return config;
}

void print_config(Type_Config auxConfig, t_log* log_Master){
	log_info(log_Master, "----------------------");
	log_info(log_Master, "Configuracion:");
	log_info(log_Master, "PUERTO = %d",auxConfig.YAMA_PUERTO);
	log_info(log_Master, "PUNTO_MONTAJE = %s",auxConfig.YAMA_IP);
	log_info(log_Master, "----------------------");
}
