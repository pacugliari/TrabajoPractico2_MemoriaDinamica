/*
 * ejercicio44.h
 *
 *  Created on: 31 oct. 2020
 *      Author: PACugliari
 */

#ifndef CODIGO_LIB_EJERCICIO44_H_
#define CODIGO_LIB_EJERCICIO44_H_

typedef struct{
    repuestos2_t repuesto;
    int cantidad;
}extraccionRepuestos_t;

typedef struct{
	extraccionRepuestos_t dato;
	void *anterior;
	void *siguiente;
}listaExtracciones_t;

void ejercicio44();

#endif /* CODIGO_LIB_EJERCICIO44_H_ */
