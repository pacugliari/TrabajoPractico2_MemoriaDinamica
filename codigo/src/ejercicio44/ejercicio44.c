/*
 EJERCICIO 44:

El servicio técnico utiliza la pila generada en el ejercicio 43 en su labor diaria.
 Cada técnico toma una tarea de la pila y genera un orden de extracción de repuestos al depósito.
  Para optimizar los viajes al depósito se arma una lista con los repuestos que cada orden necesita
  utilizando la siguiente estructura:

typedef struct{
    repuestos_t repuesto;
    int cantidad;
}extraccionRepuestos_t;

Se pide cargar la lista de repuestos solicitados por los técnicos.
Tener en cuenta que varios técnicos pueden necesitar la misma parte, y en esos casos se debe incrementar
la cantidad pedida en la lista.
 */

#include "../../lib/compartida.h"

void generarTarea(pilaRepuestos_t** primeroPila,listaExtracciones_t** primeroExtrac,listaExtracciones_t** ultimoExtrac){
	pilaRepuestos_t* auxiliar=NULL;
	extraccionRepuestos_t tarea;
	listaExtracciones_t* cursor;
	listaExtracciones_t* auxiliarTarea;
	int encontrado =0 ;

	if ((*primeroPila)!=NULL){ // SI LA PILA DE ORDENES NO ESTA VACIA
		auxiliar=(*primeroPila);
		(*primeroPila) = (*primeroPila)->lazo;
		tarea.repuesto = auxiliar->dato;
		printf("Ingrese la cantidad \n");
		scanf("%d",&tarea.cantidad);
		fflush(stdin);
		free(auxiliar);

		//CARGO EN LA LISTA
		auxiliarTarea = (listaExtracciones_t*)malloc (sizeof (listaExtracciones_t));
		auxiliarTarea->dato = tarea;

		if ((*primeroExtrac)==NULL && (*ultimoExtrac)==NULL){ // lista vacia
			(*primeroExtrac)=(*ultimoExtrac)=auxiliarTarea;
			auxiliarTarea->anterior = NULL;
			auxiliarTarea->siguiente = NULL;
		}else{
			//BUSCO POSICION
			cursor = (*primeroExtrac);
			//VEO PRIMERO SI EL REPUESTO YA ESTA CARGADO
			while (cursor){
				if (0==strcmp(cursor->dato.repuesto.modelo,auxiliarTarea->dato.repuesto.modelo)){
					encontrado = 1;
					break;
				}else{
					cursor = cursor->siguiente;
				}
			}
			//SI NO EXISTE EL REPUESTO BUSCO LA POSICION DEPENDIENDO LA CANTIDAD
			if (!encontrado){
				cursor = (*primeroExtrac);
				while((cursor &&  cursor->dato.cantidad > auxiliarTarea->dato.cantidad )){//ORDENO POR CANTIDAD
					cursor = cursor->siguiente;
				}
				if (!cursor){// fin de lista
					(*ultimoExtrac)->siguiente = auxiliarTarea;
					auxiliarTarea->anterior = (*ultimoExtrac);
					auxiliarTarea->siguiente = NULL;
					(*ultimoExtrac) =auxiliarTarea;
				}else if (cursor==(*primeroExtrac)){//inicio de lista
					auxiliarTarea->siguiente = (*primeroExtrac);
					(*primeroExtrac)->anterior = auxiliarTarea;
					auxiliarTarea->anterior = NULL;
					(*primeroExtrac) = auxiliarTarea;
				}else{//posicon media
					cursor = cursor->anterior;
					auxiliarTarea->siguiente = cursor->siguiente;
					auxiliarTarea->anterior = cursor;
					((lista_t*)(cursor->siguiente))->anterior = auxiliarTarea;
					cursor->siguiente = auxiliarTarea;
				}
			}else{
				cursor->dato.cantidad += auxiliarTarea->dato.cantidad;
			}
		}
	}else{//PILA VACIA
		printf("La pila de ordenes se encuentra vacia \n");
	}
}

void verListaExtracciones(listaExtracciones_t* primero){
	printf("MODELO\t\t    CANTIDAD\n");
	while(primero){
		printf("%-20s%-8d\n",primero->dato.repuesto.modelo,primero->dato.cantidad);
		primero= primero->siguiente;
	}
}

void vaciarPilaOrdenes(pilaRepuestos_t* primeroPila){
	pilaRepuestos_t* auxiliar;
	while(primeroPila){ // no apunte a null, si apunta null la pila esta vacia
		auxiliar=primeroPila;
		primeroPila = primeroPila->lazo;
		free(auxiliar);
	}
}

void vaciarListaOrdenes(listaExtracciones_t* primeroExtrac){
	listaExtracciones_t* auxiliar;
	while(primeroExtrac){ // no apunte a null, si apunta null la pila esta vacia
		auxiliar=primeroExtrac;
		primeroExtrac = primeroExtrac->siguiente;
		free(auxiliar);
	}
}

void ejercicio44(){
	char respuesta;
	listaRepuesto2_t* primero=NULL;
	listaRepuesto2_t* ultimo=NULL;
	listaExtracciones_t* primeroExtrac=NULL;
	listaExtracciones_t* ultimoExtrac=NULL;
	pilaRepuestos_t* primeroPila = NULL;

	ordenamientoOrdenes(&primero,&ultimo,&primeroPila);
	cargarPila(primero,&primeroPila);

	do{
		printf("1) Tomar tarea de pila \n");
		printf("2) Ver lista \n");
		printf("S) Salir \n");
		scanf("%c",&respuesta);
		fflush(stdin);
		switch(respuesta){
		case '1':
			generarTarea(&primeroPila,&primeroExtrac,&ultimoExtrac);
		break;
		case '2':
			verListaExtracciones(primeroExtrac);
		break;
		case 's':
		case 'S':
			//LIBERO MEMORIA
			vaciarPilaOrdenes(primeroPila);
			vaciarListaOrdenes(primeroExtrac);
		break;
		}
	}while(respuesta!= 'S' && respuesta!= 's');
}
