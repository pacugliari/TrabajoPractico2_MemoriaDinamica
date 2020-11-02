/*
EJERCICIO 41:

El depósito de la empresa CosmeFulanito necesita cargar su stock de repuestos en forma ordenada.
 Para dicha tarea se solicitó categorizar a los respuestos bajo la siguiente estructura de datos:

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];
   chat ubicacion[100];
}repuestos_t;
Los repuestos no están ordenados, se solicita cargarlos en una lista, la cual ordene por descripción a los
repuestos para luego guardarlos en un archivo de stock con organización secuencial.

Imprimir en pantalla la lista con cada inserción.
El archivo se generará cuando el usuario decide no cargar mas productos.
 */

#include "../../lib/compartida.h"

repuestos_t pedirRepuesto(){
	repuestos_t producto;
	printf("Ingrese el numero de parte \n");
	scanf("%ld",&producto.partNumber);
	fflush(stdin);
	printf("Ingrese el numero serial \n");
	scanf("%ld",&producto.serialNumber);
	fflush(stdin);
	printf("Ingrese la descripcion \n");
	gets(producto.descripcion);
	fflush(stdin);
	printf("Ingrese la ubicacion \n");
	gets(producto.ubicacion);
	fflush(stdin);
	printf("Ingrese la cantidad \n");
	scanf("%d",&producto.cantidad);
	fflush(stdin);
	return producto;
}

void verListaRepuestos(listaRepuesto_t* primero){

	listaRepuesto_t* cursor = primero;
	printf("N°PARTE\t\tN°SERIAL\t\tCANTIDAD\t\tDESCRIPCION\t\tUBICACION\n");
	while(cursor){
		printf("%-7ld\t\t%-8ld\t\t%-8d\t\t%-20s\t%-50s\n",cursor->dato.partNumber,cursor->dato.serialNumber,cursor->dato.cantidad,cursor->dato.descripcion,cursor->dato.ubicacion);
		cursor = cursor->siguiente;
	}
}

void cargarListaRepuestos (listaRepuesto_t** primero,listaRepuesto_t** ultimo){

	listaRepuesto_t* auxiliar=NULL;
	listaRepuesto_t* cursor=NULL;

	auxiliar = (listaRepuesto_t*)malloc (sizeof (listaRepuesto_t));
	auxiliar->dato = pedirRepuesto();

	if ((*primero)==NULL && (*ultimo)==NULL){ // lista vacia
		(*primero)=(*ultimo)=auxiliar;
		auxiliar->anterior = NULL;
		auxiliar->siguiente = NULL;
	}else{
		//BUSCO POSICION
		cursor = (*primero);
		while(cursor &&  (0 > strcmp((cursor->dato).descripcion,(auxiliar->dato).descripcion))){//ORDENO ALFABETICAMENTE DESCRIPCION
			cursor = cursor->siguiente;
		}
		if (!cursor){// fin de lista
			(*ultimo)->siguiente = auxiliar;
			auxiliar->anterior = (*ultimo);
			auxiliar->siguiente = NULL;
			(*ultimo) =auxiliar;
		}else if (cursor==(*primero)){//inicio de lista
			auxiliar->siguiente = (*primero);
			(*primero)->anterior = auxiliar;
			auxiliar->anterior = NULL;
			(*primero) = auxiliar;
		}else{//posicon media
			cursor = cursor->anterior;
			auxiliar->siguiente = cursor->siguiente;
			auxiliar->anterior = cursor;
			((lista_t*)(cursor->siguiente))->anterior = auxiliar;
			cursor->siguiente = auxiliar;
		}
	}
	verListaRepuestos((*primero));
}


void cargarArchivoRepuestos(listaRepuesto_t* primero){
	listaRepuesto_t* cursor = primero;
	listaRepuesto_t* aux;
	repuestos_t leido;
	int encontrado =0;

	FILE* archivo = fopen (STOCK,"rb+");//ABRO EL ARCHIVO
	if(!archivo){
		archivo = fopen (STOCK,"wb+");//SI NO EXISTE LO CREO
		if (!archivo){
			printf("Error en la creacion del archivo %s \n",STOCK);
			return;
		}
	}

	while(cursor){
		aux = cursor;
		//ALTA DE ARCHIVO SECUENCIAL
		//VERIFICO QUE NO EXISTA LA CLAVE,EN ESTE CASO LA CLAVE ES EL partNumber Y serialNumber
		encontrado =0;
		fread(&leido,sizeof(leido),1,archivo);
		while(!feof(archivo)){
			if (((leido.partNumber)==(cursor->dato.partNumber)) && ((leido.serialNumber)==(cursor->dato.serialNumber)) ){
				encontrado = 1;// SI YA EXISTE EN EL ARCHIVO NO LA CARGO
				break;
			}
			fread(&leido,sizeof(leido),1,archivo);
		}
		if (!encontrado)
			fwrite(&cursor->dato,sizeof(cursor->dato),1,archivo);
		cursor = cursor->siguiente;
		free(aux);
		rewind(archivo);
	}
	fclose(archivo);
}

void verArchivoRepuestos(){
	FILE* archivo = fopen (STOCK,"rb");
	if(!archivo){
		printf("Error apertura archivo %s, puede que no exista \n",STOCK);
		return;
	}
	printf("N°PARTE\t\tN°SERIAL\t\tCANTIDAD\t\tDESCRIPCION\t\tUBICACION\n");
	repuestos_t repuesto;
	fread(&repuesto,sizeof(repuesto),1,archivo);
	while(!feof(archivo)){
		printf("%-7ld\t\t%-8ld\t\t%-8d\t\t%-20s\t%-50s\n",repuesto.partNumber,repuesto.serialNumber,repuesto.cantidad,repuesto.descripcion,repuesto.ubicacion);
		fread(&repuesto,sizeof(repuesto),1,archivo);
	}
	fclose(archivo);
}

void ejercicio41(){
	char respuesta;
	listaRepuesto_t *primero=NULL;
	listaRepuesto_t *ultimo=NULL;

	do{
		printf("1) INGRESAR REPUESTOS \n");
		printf("S) SALIR \n");
		scanf("%c",&respuesta);
		fflush(stdin);
		switch(respuesta){
			case '1':
				cargarListaRepuestos (&primero,&ultimo);
			break;

			case 's':
			case 'S':
				cargarArchivoRepuestos(primero);
				verArchivoRepuestos();
			break;
		}
	}while(respuesta!='S' && respuesta!='s');
}
