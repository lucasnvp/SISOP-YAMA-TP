#ifndef STRUCTS_H_
#define STRUCTS_H_

typedef struct ArchivoBloques{
	uint32_t bloque;
	char* C1_Nodo;
	uint32_t C1_Bloque;
	char* C2_Nodo;
	uint32_t C2_Bloque;
	uint32_t finBloque;
}t_bloques;

#endif /* STRUCTS_H_ */
