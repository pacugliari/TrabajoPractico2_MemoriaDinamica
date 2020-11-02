/*
 * main.c
 *
 *  Created on: 10 oct. 2020
 *      Author: PACugliari
 */

#include "../lib/compartida.h"


int main(){
	setvbuf(stdout, NULL, _IONBF, 0);//AGREGADO PARA EVITAR BUG CONSOLA ECLIPSE
	char respuesta;
	do{
		printf("\n***TRABAJO PRACTICO 2 - MEMORIA DINAMICA***\n\n");
		printf("\t1) EJECUTAR EJERCICIO 35\n");
		printf("\t2) EJECUTAR EJERCICIO 36 \n");
		printf("\t3) EJECUTAR EJERCICIO 37 \n");
		printf("\t4) EJECUTAR EJERCICIO 38 \n");
		printf("\t5) EJECUTAR EJERCICIO 39 \n");
		printf("\t6) EJECUTAR EJERCICIO 40 \n");
		printf("\n***SEGUNDA PARTE TP***\n\n");
		printf("\t7) EJECUTAR EJERCICIO 41 \n");
		printf("\t8) EJECUTAR EJERCICIO 42 \n");
		printf("\t9) EJECUTAR EJERCICIO 43 \n");
		printf("\tA) EJECUTAR EJERCICIO 44 \n");
		printf("\nS) SALIR \n");
		scanf("%c",&respuesta);
		fflush(stdin);
		switch (respuesta){
			case '1':
				ejercicio35();
			break;
			case '2':
				ejercicio36();
			break;
			case '3':
				ejercicio37();
			break;
			case '4':
				ejercicio38();
			break;
			case '5':
				ejercicio39();
			break;
			case '6':
				ejercicio40();
			break;
			case '7':
				ejercicio41();
			break;
			case '8':
				ejercicio42();
			break;
			case '9':
				ejercicio43();
			break;
			case 'A':
				ejercicio44();
			break;
		}
	}while(respuesta!='S' && respuesta != 's');


	return 0;
}
