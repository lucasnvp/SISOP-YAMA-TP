#ifndef SETUP_H_
#define SETUP_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/stat.h>

#include "commons/config.h"
#include "commons/string.h"

static const char* TAMANIO_BLOQUE = "TAMANIO_BLOQUES=1000000\n";
static const char* CANTIDAD_BLOQUE = "CANTIDAD_BLOQUES=100\n";
static const char* puntoDeMontaje = "/home/utnso/Blacklist/DataNode/";
static const char* montajeBloques = "/home/utnso/Blacklist/DataNode/Bloques/";

t_config * dataBinConfig;

FILE * databin;

int i;
uint32_t CANT_BLOQUES;
uint32_t TAMANIO_BLOQUES;

void setup(char* RUTA_DATABIN);
void new_data_setup(char* RUTA_DATABIN);
void data_setup(char* RUTA_DATABIN);
void bloques_setup();
void carpetas_setup();

#endif /* SETUP_H_ */
