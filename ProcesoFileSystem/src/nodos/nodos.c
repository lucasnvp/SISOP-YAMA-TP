#include "nodos.h"

void init_list_nodo(){
	LIST_NODOS = list_create();
}

void add_nodo(t_nodo* nodo){
	list_add(LIST_NODOS, nodo);
}
