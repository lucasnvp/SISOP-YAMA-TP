#include "estructuras.h"

t_nodo* New_Nodo(char* nombre, uint32_t puertoWorker, uint32_t tamanio){
	t_nodo* nodo = malloc(sizeof(t_nodo));
	nodo->nombre = strdup(nombre);
	nodo->ip = "0.0.0.0";
	nodo->socket = 0;
	nodo->puertoDataNode = 0;
	nodo->puertoWorker = puertoWorker;
	nodo->tamanio = tamanio;
	nodo->conectado = true;
	return nodo;
}
