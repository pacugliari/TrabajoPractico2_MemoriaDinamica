/*
 * ejercicio35.h
 *
 *  Created on: 10 oct. 2020
 *      Author: PACugliari
 */

#ifndef HEADERS_EJERCICIO35_H_
#define HEADERS_EJERCICIO35_H_


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

#define CONTACTOS "codigo/archivos/contactos.dat"

void ejercicio35();
void imprimirPersona(persona_t);

#endif /* HEADERS_EJERCICIO35_H_ */
