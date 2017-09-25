#ifndef ESTRUCTURAS_H_
#define ESTRUCTURAS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

typedef struct NodoType{
	char* nombre;
	char* ip;
	uint32_t socket;
	uint32_t puertoWorker;
	uint32_t puertoDataNode;
	uint32_t tamanio;
	uint32_t tamanioLibreNodo;
	bool conectado;
}t_nodo;

t_nodo* New_Nodo(char* nombre, uint32_t puertoWorker, uint32_t tamanio);
void free_nodo(t_nodo* nodo);

#endif /* ESTRUCTURAS_H_ */
