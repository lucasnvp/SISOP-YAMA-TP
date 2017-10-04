#ifndef ARCHIVOS_H_
#define ARCHIVOS_H_

#include "commons/collections/list.h"

#include "../estructuras/structs.h"

t_list * LIST_ARCHIVOS;

void setup_archivos();
t_archivo* new_file(uint32_t sizeFile, char* tipo, uint32_t dir_Padre, t_bloque* bloques);

#endif /* ARCHIVOS_H_ */
