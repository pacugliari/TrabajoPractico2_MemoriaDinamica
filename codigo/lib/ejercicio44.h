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

listaExtracciones_t* ejercicio44();
void generarTarea(pilaRepuestos_t** primeroPila,listaExtracciones_t** primeroExtrac,listaExtracciones_t** ultimoExtrac);
void verListaExtracciones(listaExtracciones_t* primero);

#endif /* CODIGO_LIB_EJERCICIO44_H_ */
