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
   char fecha[11];
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

#define ORDEN "codigo/archivos/ordenes.dat"

void ejercicio43();
void ordenamientoOrdenes (listaRepuesto2_t** primero,listaRepuesto2_t** ultimo,	pilaRepuestos_t** primeroPila);
void cargarPila(listaRepuesto2_t* primero,pilaRepuestos_t** primeroPila);

#endif /* CODIGO_LIB_EJERCICIO43_H_ */
