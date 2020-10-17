/*
EJERCICIO 38:

Hacer una cola con los valores muestreados de un cuarto de ciclo de una señal sinusoidal,
en 8 bits, para luego recorrerla y recomponer la señal completa. Las muetras deberán ir de 127 a -127
 utilizando el bit más significativo en 1 para los valores negativos y en 0 para los valores positivos.
 Imprimir en pantalla los valores.
 */

#include "../../lib/compartida.h"

void aColar (unsigned char dato,cola_t** primero,cola_t** ultimo){
	cola_t* auxiliar = (cola_t*)malloc (sizeof (cola_t));
	auxiliar->dato = dato;

	if ((*primero)==NULL && (*ultimo)==NULL){ // lista vacia
		(*primero)=(*ultimo)=auxiliar;
		auxiliar->anterior = NULL;
		auxiliar->siguiente = NULL;
	}else{//colocar al final
		(*ultimo)->siguiente = auxiliar;
		auxiliar->anterior = (*ultimo);
		auxiliar->siguiente = NULL;
		(*ultimo) = auxiliar;
	}
}

void generarCola(cola_t** primero,cola_t** ultimo,int desde,int hasta){
	int muestra = desde;
	unsigned char valorACargar;
	while (muestra <= hasta){
		valorACargar=0;
		if (muestra < 0){
			valorACargar = muestra*(-1);//CONVIERTO NUMERO POSITIVO
			valorACargar = valorACargar | (1 << 7); // ENCIENDO EL BIT MAS SIGNIFICATIVO PARA INDICAR EL SIGNO
		}else{
			valorACargar = muestra;
		}
		muestra++;
		aColar(valorACargar,primero,ultimo);
	}

}

void mostrarValores(cola_t** primero){
	cola_t* auxiliar;
	int saltoLinea = 0;
	while((*primero)){
		auxiliar = (*primero);
		(*primero) = (*primero)->siguiente;
		if(saltoLinea == 20){
			printf("\n");
			saltoLinea=0;
		}
		printf("0x%X-",auxiliar->dato);
		saltoLinea++;
		free(auxiliar);
	}
	printf("\n");
}

void ejercicio38(){
	cola_t* primero=NULL;
	cola_t* ultimo=NULL;
	int respuesta;

	do{
		printf("1) Mostrar valores \n");
		printf("0) Salir \n");
		scanf("%d",&respuesta);
		switch(respuesta){
		case 1:
			printf("Positivos senoidal: \n");
			generarCola(&primero,&ultimo,0,127);//0: DESDE, 127: HASTA
			mostrarValores(&primero);
			printf("Negativos senoidal: \n");
			primero=ultimo=NULL;
			generarCola(&primero,&ultimo,-127,0);
			mostrarValores(&primero);
		break;
		}
	}while(respuesta!=0);
}
