/*
 * ejercicio36.h
 *
 *  Created on: 12 oct. 2020
 *      Author: PACugliari
 */



#ifndef CODIGO_LIB_EJERCICIO36_H_
#define CODIGO_LIB_EJERCICIO36_H_


typedef struct lista{
	persona_t dato;
	void *anterior;
	void *siguiente;
}lista_t;

void ejercicio36();

#define CONTACTOS_ORD "codigo/archivos/contactos_ordenados.dat"

#endif /* CODIGO_LIB_EJERCICIO36_H_ */
