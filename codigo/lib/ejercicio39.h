/*
 * ejercicio39.h
 *
 *  Created on: 13 oct. 2020
 *      Author: PACugliari
 */

#ifndef CODIGO_LIB_EJERCICIO39_H_
#define CODIGO_LIB_EJERCICIO39_H_

typedef struct{
	char desc[60];
    unsigned char potencia;
    unsigned int estado;
}potencia_t;

typedef struct{
	potencia_t dato;
	void *anterior;
	void *siguiente;
}listaPotencia_t;

#define POTENCIA "codigo/archivos/potencia.dat"

void ejercicio39();


#endif /* CODIGO_LIB_EJERCICIO39_H_ */
