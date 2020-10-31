/*
 * ejercicio42.h
 *
 *  Created on: 30 oct. 2020
 *      Author: PACugliari
 */

#ifndef CODIGO_LIB_EJERCICIO42_H_
#define CODIGO_LIB_EJERCICIO42_H_

typedef struct{
	repuestos_t dato;
	void* siguiente;
	void* anterior;
}colaFallados_t;

#define STOCKN "codigo/archivos/stockN.dat" //PARA COPIAR LOS ARCHIVOS SIN ERRORES
#define STOCK_FALLO "codigo/archivos/stockFallados.dat" //PARA COPIAR LOS ARCHIVOS SIN ERRORES

void ejercicio42();

#endif /* CODIGO_LIB_EJERCICIO42_H_ */
