#ifndef NODOS_H_
#define NODOS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "commons/log.h"
#include "commons/string.h"
#include "commons/bitarray.h"
#include "commons/collections/list.h"
#include "serializador/estructuras.h"

#define CLOSE_DATANODE	3

typedef struct NodoBitMapType{
	t_nodo* nodo;
	t_bitarray* bitarray;
}t_nodo_and_bitmap;

t_list * LIST_NODOS;
uint32_t tamanioTotal;
uint32_t tamanioLibreTotal;

void setup_nodos();
void init_list_nodo();
void init_bitmap_por_nodo(char* pathNodoBitmap, uint32_t sizeNodo);
t_bitarray* reload_bitmap_por_nodo(char* pathNodoBitmap);
void add_nodo(t_nodo* nodo);
void sizeFS();
void close_nodes_conexions();
void persistir_nodos();
void persistir_bitmaps();

#endif /* NODOS_H_ */
