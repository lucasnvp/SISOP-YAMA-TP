#include "setup.h"

t_bin* setup(char* RUTA_DATABIN, t_log* log_Console){
	if(access(RUTA_DATABIN, F_OK) != -1){
		return data_setup(RUTA_DATABIN, log_Console);
	} else{
		log_warning(log_Console,"Error al leer el archivo BIN");
		exit(EXIT_SUCCESS);
	}
}

t_bin* data_setup(char* RUTA_DATABIN, t_log* log_Console){
	t_bin* bin = malloc(sizeof(t_bin));

	struct stat binStat;

	bin->fd = open(RUTA_DATABIN,O_RDWR);

	fstat(bin->fd,&binStat);

	bin->size = binStat.st_size;

	bin->binmap = mmap(0, bin->size, PROT_READ | PROT_WRITE, MAP_SHARED, bin->fd, 0);

	log_info(log_Console,"Se mapeo el archivo BIN");

	return bin;
}
