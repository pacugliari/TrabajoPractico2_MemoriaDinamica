/*
EJERCICIO 39:

Hacer un programa que tome los datos de medición de potencia, cargados por el usuario,
de un sistema de medición a distancia.

Los datos que cargará el usuario tienen la siguiente estructura:

    char desc[60];
    unsigned char potencia;
    unsigned int estado;
Donde estado es la multiplicación del valor ASCII de la primer letra de la descripción por la potencia.
 Los datos cargados se deberán guardar en una lista ordenada, de mayor a menor, del valor de potencia.
  Una vez finalizada la carga guardar los datos en un archivo de organización directa llamado "potencia.dat"
  imprimiendo en pantalla los datos.
 */

#include "../../lib/compartida.h"

potencia_t pedirDatosPotencia(){
	potencia_t datos;
	int entrada;
	printf("Ingrese la descripcion \n");
	fflush(stdin);
	gets(datos.desc);
	fflush(stdin);
	do{
		printf("Ingrese la potencia (0 a 255) \n");
		scanf("%d",&entrada);
		datos.potencia = (unsigned char)entrada;
	}while(entrada < 0 || entrada > 255);
	datos.estado = ((int)datos.desc[0])*datos.potencia;
	return datos;
}

void cargarListaPotencia(potencia_t datos,listaPotencia_t** primero,listaPotencia_t** ultimo){

	listaPotencia_t* cursor;
	listaPotencia_t* auxiliar = (listaPotencia_t*)malloc (sizeof (listaPotencia_t));
	auxiliar->dato = datos;


	if ((*primero)==NULL && (*ultimo)==NULL){ // lista vacia
		(*primero)=(*ultimo)=auxiliar;
		auxiliar->anterior = NULL;
		auxiliar->siguiente = NULL;
	}else{
		//BUSCO POSICION
		cursor = (*primero);

		while(cursor && (cursor->dato.potencia > auxiliar->dato.potencia)){//ORDENO MAYOR A MENOR
			cursor = cursor->siguiente;

		}
		if (!cursor){// fin de lista
			(*ultimo)->siguiente = auxiliar;
			auxiliar->anterior = (*ultimo);
			auxiliar->siguiente = NULL;
			(*ultimo) = auxiliar;
		}else if (cursor==(*primero)){//inicio de lista
			auxiliar->siguiente = (*primero);
			(*primero)->anterior = auxiliar;
			auxiliar->anterior = NULL;
			(*primero) = auxiliar;
		}else{//posicon media
			cursor = cursor->anterior;
			auxiliar->siguiente = cursor->siguiente;
			auxiliar->anterior = cursor;
			((listaPotencia_t*)(cursor->siguiente))->anterior = auxiliar;
			cursor->siguiente = auxiliar;
		}
	}

}

void cargarArchivoPotencia (listaPotencia_t* primero){

	//CARGO LA LISTA EN EL ARCHIVO DIRECTO
	potencia_t registro;
	listaPotencia_t* cursor;

	FILE*  archivo = fopen (POTENCIA,"wb+");
	registro.desc[0] = '-'; // registro de inicio de archivo directo
	fwrite(&registro,sizeof(registro),1,archivo);
	if (!archivo){
		printf("Error en la creacion del archivo %s",POTENCIA);
		return;
	}

	cursor = primero;
	while(cursor){
		fseek(archivo,(-1L)*(long)sizeof(registro),SEEK_END);
		fread(&registro,sizeof(registro),1,archivo);
		fseek(archivo,0L,SEEK_END);
		fwrite(&(cursor->dato),sizeof(registro),1,archivo);
		cursor = cursor->siguiente;
	}

	fclose(archivo);

}

void verArchivoPotencia(){
	FILE* archivo = fopen (POTENCIA,"rb");
	potencia_t registro;
	if(!archivo){
		printf("Error en la apertura del archivo %s",POTENCIA);
	}
	printf ("***LISTADO DE POTENCIAS***\n\n");
		printf ("POTENCIA			ESTADO			DESCRIPCION\n");
		printf ("--------------------------------------------------------------------------------------\n");
	fread(&registro,sizeof(registro),1,archivo);
	while(!feof(archivo)){
		if (registro.desc[0] != '-'){
			printf ("%03d				%08d		%-60s\n",registro.potencia,registro.estado,registro.desc);
		}
		fread(&registro,sizeof(registro),1,archivo);
	}
}

void liberarMemoria(listaPotencia_t* primero){
	listaPotencia_t* cursor;
	listaPotencia_t* auxiliar;
	cursor = primero;
	while(cursor){
		auxiliar= cursor;
		cursor = cursor->siguiente;
		free(auxiliar);
	}
}

void ejercicio39(){
	potencia_t datos;
	int respuesta;
	listaPotencia_t* primero = NULL;
	listaPotencia_t* ultimo = NULL;

	do{
		printf("1) Cargar datos \n");
		printf("2) Ver archivo \n");
		printf("0) Salir \n");
		scanf("%d",&respuesta);
		switch(respuesta){
		case 1:
			datos = pedirDatosPotencia();
			cargarListaPotencia(datos,&primero,&ultimo);
		break;
		case 2:
			cargarArchivoPotencia(primero);
			verArchivoPotencia();
		break;
		}


	}while(respuesta!=0);


	liberarMemoria(primero);

}

