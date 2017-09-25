#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <inttypes.h>

uint32_t bytesToMB(uint32_t bytes);
uint32_t mbToBytes(uint32_t mBytes);
uint32_t ValidarArchivo(char* path);

#endif /* FUNCTIONS_H_ */
