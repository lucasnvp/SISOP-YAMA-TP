#include "setup.h"

void setup(char* RUTA_DATABIN){
	carpetas_setup();

	if(access(RUTA_DATABIN, F_OK) != -1){
		data_setup(RUTA_DATABIN);
	} else{
		new_data_setup(RUTA_DATABIN);
		data_setup(RUTA_DATABIN);
	}

	//Bloques
	bloques_setup(RUTA_DATABIN);
}

void new_data_setup(char* RUTA_DATABIN){
	databin = fopen(RUTA_DATABIN, "w+b");
	fwrite(TAMANIO_BLOQUE,1,strlen(TAMANIO_BLOQUE),databin);
	fwrite(CANTIDAD_BLOQUE,1,strlen(CANTIDAD_BLOQUE),databin);
	fclose(databin);
}

void data_setup(char* RUTA_DATABIN){
	//Obtener Datos Metadata
	dataBinConfig = config_create(RUTA_DATABIN);
	CANT_BLOQUES = config_get_int_value(dataBinConfig, "CANTIDAD_BLOQUES");
	TAMANIO_BLOQUES = config_get_int_value(dataBinConfig, "TAMANIO_BLOQUES");
	config_destroy(dataBinConfig);
}

void bloques_setup(){
	FILE * newBloque;
	for(i=1; i <= CANT_BLOQUES; i++){
		char* nroBloque = string_new();
		string_append(&nroBloque, montajeBloques);
		string_append(&nroBloque, string_itoa(i));
		newBloque = fopen(nroBloque,"w+b");
		fclose(newBloque);
		free(nroBloque);
	}
}

void carpetas_setup(){
	//Crea la carpeta de montaje
	mkdir(puntoDeMontaje, 0777);
	//Crea la carpeta Bloques
	mkdir(montajeBloques, 0777);
}
