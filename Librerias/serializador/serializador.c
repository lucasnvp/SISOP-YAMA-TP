#include "serializador.h"

t_stream* stream_create(int size) {
	t_stream* stream = malloc(sizeof(t_stream));
	stream->size = size;
	stream->data = malloc(size);
	return stream;
}

void stream_destroy(t_stream* stream) {
	free(stream->data);
	free(stream);
}

void serializar_int(uint32_t socket, uint32_t number){
	send_data(socket, &number, sizeof(uint32_t));
}

uint32_t deserializar_int(uint32_t socket){
	uint32_t aux;
	uint32_t bytesRecibidos = recive_data(socket,&aux,sizeof(uint32_t));
	if(bytesRecibidos <= 0){
		aux = bytesRecibidos;
	}
	return aux;
}

void serializar_string(int client, char* stringToSend){
	void* ENVIAR = malloc(strlen(stringToSend) + 1);
	uint32_t offset = 0;
	uint32_t size_to_send;

	size_to_send = strlen(stringToSend) + 1;
	memcpy(ENVIAR + offset, stringToSend, size_to_send);
	offset += size_to_send;

	serializar_int(client, offset);
	send_data(client, ENVIAR, offset);
	free(ENVIAR);
}

char* deserializar_string(int servidor){
	uint32_t buffer_size = deserializar_int(servidor);
	void* buffer = malloc(buffer_size);
	recive_data(servidor, buffer, buffer_size);
	char* stringToRecived = strdup(buffer);
	free(buffer);
	return stringToRecived;
}

void serializar_nodo(uint32_t socket, t_nodo* nodo){
	uint32_t datos_size = sizeof(t_nodo) + (strlen(nodo->nombre) + 1) + (strlen(nodo->ip) + 1);
	void* ENVIAR = malloc(datos_size);
	uint32_t offset = 0;
	uint32_t size_to_send;

	size_to_send = strlen(nodo->nombre) + 1;
	memcpy(ENVIAR + offset, nodo->nombre, size_to_send);
	offset += size_to_send;

	size_to_send = strlen(nodo->ip) + 1;
	memcpy(ENVIAR + offset, nodo->ip, size_to_send);
	offset += size_to_send;

	size_to_send = sizeof(nodo->socket);
	memcpy(ENVIAR + offset, &(nodo->socket),size_to_send);
	offset += size_to_send;

	size_to_send = sizeof(nodo->puertoDataNode);
	memcpy(ENVIAR + offset, &(nodo->puertoDataNode),size_to_send);
	offset += size_to_send;

	size_to_send = sizeof(nodo->puertoWorker);
	memcpy(ENVIAR + offset, &(nodo->puertoWorker),size_to_send);
	offset += size_to_send;

	size_to_send = sizeof(nodo->tamanio);
	memcpy(ENVIAR + offset, &(nodo->tamanio),size_to_send);
	offset += size_to_send;

	size_to_send = sizeof(nodo->conectado);
	memcpy(ENVIAR + offset, &(nodo->conectado),size_to_send);
	offset += size_to_send;

	serializar_int(socket, offset);
	send_data(socket, ENVIAR, offset);
	free(ENVIAR);
}

t_nodo* deserializar_nodo(uint32_t socket){
	uint32_t buffer_size = deserializar_int(socket);
	void* buffer = malloc(buffer_size);
	t_nodo* nodo = malloc(sizeof(t_nodo));
	uint32_t offset = 0;
	uint32_t size_to_recive;

	recive_data(socket, buffer, buffer_size);

	nodo->nombre = strdup(buffer + offset);
	offset += strlen(nodo->nombre) + 1;

	nodo->ip = strdup(buffer + offset);
	offset += strlen(nodo->ip) + 1;

	size_to_recive = sizeof(nodo->socket);
	memcpy(&nodo->socket, buffer + offset, size_to_recive);
	offset += size_to_recive;

	size_to_recive = sizeof(nodo->puertoDataNode);
	memcpy(&nodo->puertoDataNode, buffer + offset, size_to_recive);
	offset += size_to_recive;

	size_to_recive = sizeof(nodo->puertoWorker);
	memcpy(&nodo->puertoWorker, buffer + offset, size_to_recive);
	offset += size_to_recive;

	size_to_recive = sizeof(nodo->tamanio);
	memcpy(&nodo->tamanio, buffer + offset, size_to_recive);
	offset += size_to_recive;

	size_to_recive = sizeof(nodo->conectado);
	memcpy(&nodo->conectado, buffer + offset, size_to_recive);
	offset += size_to_recive;

	free(buffer);
	return nodo;
}

