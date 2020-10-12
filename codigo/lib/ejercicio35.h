/*
 * ejercicio35.h
 *
 *  Created on: 10 oct. 2020
 *      Author: PACugliari
 */

#ifndef HEADERS_EJERCICIO35_H_
#define HEADERS_EJERCICIO35_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct{
	char nombre[20];
	char apellido[20];
	int edad;
	long telefono;
	char mail[50];
}persona_t;

typedef struct {
    persona_t dato;
    void *lazo;
} pila_t;

void ejercicio35();

#endif /* HEADERS_EJERCICIO35_H_ */
