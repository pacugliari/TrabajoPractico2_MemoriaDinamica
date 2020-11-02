/*
 * ejercicio37.h
 *
 *  Created on: 12 oct. 2020
 *      Author: PACugliari
 */

#ifndef CODIGO_LIB_EJERCICIO37_H_
#define CODIGO_LIB_EJERCICIO37_H_

typedef struct {
	long clave; //Clave o Id del registro
	char d[30]; // Descripcion
	unsigned char tipo; //Tipo de datos como entero sin signo
	char b; //'A':Alta 'B':Baja
}datos_t;

typedef struct{
	long clave;
	int posicion;
}nodo_t;

typedef struct {
    nodo_t dato;
    void *lazo;
} pila2_t;

#define DATOS "codigo/archivos/datos.dat"

void ejercicio37();

#endif /* CODIGO_LIB_EJERCICIO37_H_ */
