#ifndef NODOS_H_
#define NODOS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "commons/log.h"
#include "commons/collections/list.h"
#include "serializador/estructuras.h"

t_list * LIST_NODOS;

void init_list_nodo();
void add_nodo(t_nodo* nodo);
//Persistir nodos

#endif /* NODOS_H_ */
