/*
 * ejercicio43.h
 *
 *  Created on: 31 oct. 2020
 *      Author: PACugliari
 */

#ifndef CODIGO_LIB_EJERCICIO43_H_
#define CODIGO_LIB_EJERCICIO43_H_

#define ANIO_ACTUAL 2020

typedef struct{
   long numeroDeOrden;
   char cliente[40];
   char descripciondeFalla[200];
   char modelo[65];
   char fecha[10];
   char hora[10];
}repuestos2_t;

typedef struct {
    repuestos2_t dato;
    void *lazo;
} pilaRepuestos_t;

typedef struct{
	repuestos2_t dato;
	void *anterior;
	void *siguiente;
}listaRepuesto2_t;

void ejercicio43();

#endif /* CODIGO_LIB_EJERCICIO43_H_ */
