/*
 * ejercicio41.h
 *
 *  Created on: 30 oct. 2020
 *      Author: PACugliari
 */

#ifndef CODIGO_LIB_EJERCICIO41_H_
#define CODIGO_LIB_EJERCICIO41_H_

typedef struct{
	long partNumber;
	long serialNumber;
	char descripcion[40];
	char ubicacion[100];
	int cantidad;//CAMPO PARA EJERCICIO 45
}repuestos_t;

typedef struct{
	repuestos_t dato;
	void *anterior;
	void *siguiente;
}listaRepuesto_t;

void ejercicio41();

#define STOCK "codigo/archivos/stock.dat"
#endif /* CODIGO_LIB_EJERCICIO41_H_ */
