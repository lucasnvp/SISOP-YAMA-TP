#include "nodos.h"

void setup_nodos(){
	init_list_nodo();

	if(ValidarArchivo("/home/utnso/Blacklist/metadata/nodos.bin")){
		//todo: Levantar la config de los nodos
	} else{
		//todo: FS en blanco
		mkdir("/home/utnso/Blacklist/metadata", 0777);
		mkdir("/home/utnso/Blacklist/metadata/bitmaps", 0777);
	}

}

void init_list_nodo(){
	LIST_NODOS = list_create();
	tamanioTotal = 0;
	tamanioLibreTotal = 0;
	punteroAlUltimoNodoEscrito = 0;
}

void init_bitmap_por_nodo(char* pathNodoBitmap, uint32_t sizeNodo){
	FILE* nodobitmap = fopen(pathNodoBitmap, "w+b");
	char data[sizeNodo];
	t_bitarray* bitarray_aux = bitarray_create_with_mode(data,sizeof(data),LSB_FIRST);
	uint32_t i;
	for(i=0; i <= sizeNodo; i++){
		bitarray_clean_bit(bitarray_aux, i);
	}
	fwrite(bitarray_aux,1,sizeof(bitarray_aux),nodobitmap);
	fclose(nodobitmap);
}

t_bitarray* reload_bitmap_por_nodo(char* pathNodoBitmap){
	struct stat nodobitmapStat;
	int32_t fd = open(pathNodoBitmap, O_RDWR);
	fstat(fd,&nodobitmapStat);
	char* mmapBitmap = mmap(0,nodobitmapStat.st_size,PROT_READ|PROT_WRITE, MAP_SHARED, fd,0);
	t_bitarray* bitarray = bitarray_create_with_mode(mmapBitmap,nodobitmapStat.st_size, LSB_FIRST);
	return bitarray;
}

void add_nodo(t_nodo* nodo){
	t_nodo_and_bitmap* nodoAndBitmap = malloc(sizeof(t_nodo_and_bitmap));
	nodoAndBitmap->nodo = nodo;

	//Compruebo si ya tenia un bit map
	char* pathNodoBitMap = string_new();
	string_append_with_format(&pathNodoBitMap, "/home/utnso/Blacklist/metadata/%s.dat", nodo->nombre);
	if(ValidarArchivo(pathNodoBitMap)){
		nodoAndBitmap->bitarray = reload_bitmap_por_nodo(pathNodoBitMap);
	} else{
		init_bitmap_por_nodo(pathNodoBitMap, nodo->tamanio);
		nodoAndBitmap->bitarray = reload_bitmap_por_nodo(pathNodoBitMap);
	}

	list_add(LIST_NODOS, nodoAndBitmap);
}

void sizeFS(){
	void size_nodo(void* element){
		t_nodo_and_bitmap* nodo = element;
		tamanioTotal += nodo->nodo->tamanio;
//		tamanioLibreTotal += nodo->tamanioLibreNodo;
	}

	list_iterate(LIST_NODOS, size_nodo);
}

void close_nodes_conexions(){
	void close_nodo(void* element){
		t_nodo_and_bitmap* nodo = element;
		serializar_int(nodo->nodo->puertoDataNode, CLOSE_DATANODE);
		// todo: Falta Persistir los bitmaps
		// todo: sincronizar lo de los mmaps
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
	string_append_with_format(&tamanio, "TAMANIO=%i\n", string_itoa(tamanioTotal));
	fwrite(tamanio,1,strlen(tamanio),nodos);
	free(tamanio);

	//Tamanio free del FS
	char* tamanioFree = string_new();
	string_append_with_format(&tamanioFree, "LIBRE=%i\n", string_itoa(tamanioLibreTotal));
	fwrite(tamanioFree,1,strlen(tamanioFree),nodos);
	free(tamanioFree);

	//Cierro el archivo
	fclose(nodos);
}

void persistir_bitmaps(){
	//Crea la carpeta de montaje
	mkdir("/home/utnso/Blacklist/metadata/bitmaps", 0777);
}

uint32_t reservar_bloques(uint32_t cantBloques){
	uint32_t i;
	t_nodo_and_bitmap* nodoC1;
	t_nodo_and_bitmap* nodoC2;

	for(i = 0; i < cantBloques; i++){
		printf("Reservar bloque %i\n", i);
		nodoC1 = list_get(LIST_NODOS, punteroAlUltimoNodoEscrito);
		printf("Copia 1 = %s - Bloque: x \n", nodoC1->nodo->nombre);
		nodo_next();
		nodoC2 = list_get(LIST_NODOS, punteroAlUltimoNodoEscrito);
		printf("Copia 2 = %s - Bloque: x \n", nodoC2->nodo->nombre);
	}
}

uint32_t nodo_next(){
	punteroAlUltimoNodoEscrito++;
	if(list_size(LIST_NODOS) <= punteroAlUltimoNodoEscrito){
		punteroAlUltimoNodoEscrito = 0;
	}
}
