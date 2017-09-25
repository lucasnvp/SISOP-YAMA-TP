#include "nodos.h"

void init_list_nodo(){
	LIST_NODOS = list_create();
	tamanioTotal = 0;
	tamanioLibreTotal = 0;
}

void add_nodo(t_nodo* nodo){
	list_add(LIST_NODOS, nodo);
}

uint32_t sizeFS(){
	void size_nodo(void* element){
		t_nodo* nodo = element;
		tamanioTotal += nodo->tamanio;
//		tamanioLibreTotal += nodo->tamanioLibreNodo;
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

void persistir_nodos(){
	//Crea la carpeta de montaje
	mkdir("/home/utnso/Blacklist/metadata", 0777);
	//Abro el archivo en modo escritura
	FILE* nodos = fopen("/home/utnso/Blacklist/metadata/nodos.bin", "w+b");

	//Tamanio total del FS
	char* tamanio = string_new();
	string_append(&tamanio, "TAMANIO=");
	string_append(&tamanio, string_itoa(tamanioTotal));
	string_append(&tamanio, "\n");
	fwrite(tamanio,1,strlen(tamanio),nodos);
	free(tamanio);

	//Tamanio free del FS
	char* tamanioFree = string_new();
	string_append(&tamanioFree, "LIBRE=");
	string_append(&tamanioFree, string_itoa(tamanioLibreTotal));
	string_append(&tamanio, "\n");
	fwrite(tamanioFree,1,strlen(tamanioFree),nodos);
	free(tamanioFree);

	//Cierro el archivo
	fclose(nodos);
}
