/*
 * main.c
 *
 *  Created on: 10 oct. 2020
 *      Author: PACugliari
 */

#include "../lib/compartida.h"


int main(){
	setvbuf(stdout, NULL, _IONBF, 0);//AGREGADO PARA EVITAR BUG CONSOLA ECLIPSE
	int respuesta;
	do{
		printf("***TRABAJO PRACTICO 2 - MEMORIA DINAMICA\n");
		printf("1) EJECUTAR EJERCICIO 35\n");
		printf("2) EJECUTAR EJERCICIO 36 \n");
		printf("0) SALIR \n");
		scanf("%d",&respuesta);
		switch (respuesta){
			case 1:
				ejercicio35();
			break;
			case 2:
				ejercicio36();
			break;
		}
	}while(respuesta!=0);


	return 0;
}
