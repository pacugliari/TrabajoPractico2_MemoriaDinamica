/*
 * ejercicio40.h
 *
 *  Created on: 13 oct. 2020
 *      Author: PACugliari
 */

#ifndef CODIGO_LIB_EJERCICIO40_H_
#define CODIGO_LIB_EJERCICIO40_H_

#define toggleBit(var,bit) var=var^(1<<bit)

typedef struct{
	potencia_t dato;
	void* lazo;
}pilaPotencia_t;

void ejercicio40();

#define SALIDA "codigo/archivos/salida.dat"

#endif /* CODIGO_LIB_EJERCICIO40_H_ */
