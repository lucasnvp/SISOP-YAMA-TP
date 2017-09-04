#ifndef SERIALIZADOR_H_
#define SERIALIZADOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#include "/home/utnso/Blacklist/tp-2017-2c-Blacklist/Librerias/servidor/servidor.h"

typedef struct {
	char* data;
	int size;
} t_stream;

int i, j;

t_stream* stream_create(int size);
void stream_destroy(t_stream* stream);

void serializar_int(uint32_t socket, uint32_t number);
uint32_t deserializar_int(uint32_t socket);

void serializar_string(int client, char* stringToSend);
char* deserializar_string(int servidor);

#endif /* SERIALIZADOR_H_ */
