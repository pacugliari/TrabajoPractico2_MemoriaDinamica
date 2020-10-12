/*
 * main.c
 *
 *  Created on: 10 oct. 2020
 *      Author: PACugliari
 */

#include "../lib/ejercicio35.h"


int main(){
	setvbuf(stdout, NULL, _IONBF, 0);//AGREGADO PARA EVITAR BUG CONSOLA ECLIPSE

	ejercicio35();

	return 0;
}
