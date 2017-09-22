#include "nodos.h"

void init_list_nodo(){
	LIST_NODOS = list_create();
	tamanioTotal = 0;
}

void add_nodo(t_nodo* nodo){
	list_add(LIST_NODOS, nodo);
}

uint32_t sizeFS(){
	void size_nodo(void* element){
		t_nodo* nodo = element;
		tamanioTotal += nodo->tamanio;
	}

	list_iterate(LIST_NODOS, size_nodo);
}

void close_nodes_conexions(){
	void close_nodo(void* element){
		t_nodo* nodo = element;
		serializar_int(nodo->puertoDataNode, CLOSE_DATANODE);
	}

	list_iterate(LIST_NODOS, close_nodo);
}
