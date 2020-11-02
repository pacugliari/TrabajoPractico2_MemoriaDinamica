/*
EJERCICIO 45:

La lista creada en el ejercicio 44 es procesada por el depósito.
 Para dicha tarea se pide hacer un programa que:

Descuente las cantidades solicitadas del archivo de stock, creado en el Ejercicio 41.
Hacer una cola con los repuestos en los que no se encontró stock suficiente para poder notificar a
los clientes la demora de la reparación.
 */

//SUPONGO QUE EL PARTNUMBER DEL EJERCICIO 41 ES EL CORRESPONDIENTE AL MODELO DEL EJERCICIO 44

#include "../../lib/compartida.h"

void aColarFaltantes (repuestos_t repuesto,colaFaltantes_t** primero,colaFaltantes_t** ultimo){
	colaFaltantes_t* auxiliar = (colaFaltantes_t*)malloc (sizeof (colaFaltantes_t));
	auxiliar->dato = repuesto;

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

void descontarStock(listaExtracciones_t* primeroExtrac,colaFaltantes_t** primero,colaFaltantes_t** ultimo){
	FILE* archivo = fopen (STOCK,"rb+");
	listaExtracciones_t* aux;
	int encontrado =0;
	repuestos_t repuesto;
	repuestos_t faltante;
	if (!archivo){
		printf("Error en la apertura del archivo %s, puede que no exista \n",STOCK);
		return;
	}

	while(primeroExtrac){
		//VOY REALIZANDO MODIFICACIONES SECUENCIALES EN EL ARCHIVO STOCK
		encontrado = 0;
		rewind(archivo);
		fread(&repuesto,sizeof(repuesto),1,archivo);
		while(!feof(archivo) && !encontrado){
			if (repuesto.partNumber == atoi(primeroExtrac->dato.repuesto.modelo)){
				if (repuesto.cantidad >= primeroExtrac->dato.cantidad){
					repuesto.cantidad -= primeroExtrac->dato.cantidad;
					fseek(archivo,(-1L)*(long)sizeof(repuesto),SEEK_CUR);
					fwrite(&repuesto,sizeof(repuesto),1,archivo);
					fclose(archivo);//PARA GUARDAR LA MODIFICACIONES
					archivo = fopen (STOCK,"rb+");
					if (!archivo){
						printf("Error en la funcion descontarStock \n");
						return;
					}
				}else{
					//CARGO LA CANTIDAD FALTANTE
					repuesto.cantidad = (primeroExtrac->dato.cantidad-repuesto.cantidad);
					aColarFaltantes(repuesto,primero,ultimo);
				}
				encontrado = 1;
			}
			fread(&repuesto,sizeof(repuesto),1,archivo);
		}
		if (!encontrado){
			printf("No se encuentra el modelo %s en el archivo %s \n",primeroExtrac->dato.repuesto.modelo,STOCK);
			faltante.partNumber = atoi(primeroExtrac->dato.repuesto.modelo);
			faltante.serialNumber = -1;
			faltante.cantidad = primeroExtrac->dato.cantidad;
			strcpy (faltante.descripcion,"Repuesto faltante");
			strcpy (faltante.ubicacion,"Repuesto faltante");
			aColarFaltantes(faltante,primero,ultimo);
		}
		aux = primeroExtrac;
		primeroExtrac = primeroExtrac->siguiente;
		free (aux);
	}
	fclose (archivo);
}

void verColaFaltantes(colaFaltantes_t* primeroFaltantes){
	printf("MODELO\t\tCANTIDAD FALTANTE\n");
	while(primeroFaltantes){
		printf("%-7ld\t\t%-d\n",primeroFaltantes->dato.partNumber,primeroFaltantes->dato.cantidad);
		primeroFaltantes = primeroFaltantes->siguiente;
	}
}

void vaciarColaFaltantes(colaFaltantes_t* primeroFaltantes){
	colaFaltantes_t* aux;
	while(primeroFaltantes){
		aux = primeroFaltantes;
		primeroFaltantes = primeroFaltantes->siguiente;
		free(aux);
	}

}

void ejercicio45(listaExtracciones_t* primeroExtrac){
	char respuesta;

	if (!primeroExtrac){
		printf("No se genero la lista del ejercicio 44 \n");
		return;
	}

	colaFaltantes_t* primeroFaltantes=NULL;
	colaFaltantes_t* ultimoFaltantes=NULL;

	printf("***LISTA EJERCICIO 44 ***\n");
	verListaExtracciones(primeroExtrac);

	do{
		printf("1) Procesar lista de repuestos \n");
		printf("2) Ver cola de faltantes \n");
		printf("S) Salir \n");
		scanf("%c",&respuesta);
		fflush(stdin);
		switch(respuesta){
			case '1':
				descontarStock (primeroExtrac,&primeroFaltantes,&ultimoFaltantes);
			break;
			case '2':
				verColaFaltantes(primeroFaltantes);
			break;
			case 's':
			case 'S':
				vaciarColaFaltantes(primeroFaltantes);
			break;
		}
	}while(respuesta != 'S' && respuesta != 's');
}
