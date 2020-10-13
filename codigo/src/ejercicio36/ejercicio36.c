/*
EJERCICIO 36:

Hacer un programa que lea al archivo "contactos.dat" creado en el Ejercicio 35 y crear una lista,
en memoria dinámica, ordenada alfabéticamente. Una vez creada la lista guardarla en un archivo de
organización directa llamado "contactos_ordenados.dat" imprimiendola en pantalla.
 */

#include "../../lib/compartida.h"


void cargarLista(persona_t persona,lista_t** primero,lista_t** ultimo,lista_t** cursor,lista_t** auxiliar){


	(*auxiliar) = (lista_t*)malloc (sizeof (lista_t));
	(*auxiliar)->dato = persona;

	if ((*primero)==NULL && (*ultimo)==NULL){ // lista vacia
		(*primero)=(*ultimo)=(*auxiliar);
		(*auxiliar)->anterior = NULL;
		(*auxiliar)->siguiente = NULL;
	}else{
		//BUSCO POSICION
		(*cursor) = (*primero);

		while(((*cursor) &&  (0 > strcmp(((*cursor)->dato).apellido,((*auxiliar)->dato).apellido)) )||
				((*cursor) && (0 == strcmp(((*cursor)->dato).apellido,((*auxiliar)->dato).apellido))
				&& (0 > strcmp(((*cursor)->dato).nombre,((*auxiliar)->dato).nombre)))){//ORDENO ALFABETICAMENTE APELLIDO Y NOMBRE
				(*cursor) = (*cursor)->siguiente;

		}
		if (!(*cursor)){// fin de lista
			(*ultimo)->siguiente = (*auxiliar);
			(*auxiliar)->anterior = (*ultimo);
			(*auxiliar)->siguiente = NULL;
			(*ultimo) = (*auxiliar);
		}else if ((*cursor)==(*primero)){//inicio de lista
			(*auxiliar)->siguiente = (*primero);
			(*primero)->anterior = (*auxiliar);
			(*auxiliar)->anterior = NULL;
			(*primero) = (*auxiliar);
		}else{//posicon media
			(*cursor) = (*cursor)->anterior;
			(*auxiliar)->siguiente = (*cursor)->siguiente;
			(*auxiliar)->anterior = (*cursor);
			((lista_t*)((*cursor)->siguiente))->anterior = (*auxiliar);
			(*cursor)->siguiente = (*auxiliar);
		}
	}

}

void cargarArchivoOrdenado(lista_t** primero,lista_t** cursor,lista_t** auxiliar){
	//CARGO LA LISTA EN EL ARCHIVO DIRECTO
	persona_t persona;

	FILE* archivo = fopen (CONTACTOS_ORD,"wb+");
	persona.edad = -1; // registro de inicio de archivo directo
	fwrite(&persona,sizeof(persona),1,archivo);
	if (!archivo){
		printf("Error en la creacion del archivo %s",CONTACTOS_ORD);
		return;
	}


	(*cursor) = (*primero);
	while((*cursor)){
		fseek(archivo,(-1L)*(long)sizeof(persona),SEEK_END);
		fread(&persona,sizeof(persona),1,archivo);
		fseek(archivo,0L,SEEK_END);
		fwrite(&((*cursor)->dato),sizeof(persona),1,archivo);
		(*auxiliar)= (*cursor);
		(*cursor) = (*cursor)->siguiente;
		free((*auxiliar));
	}

	fclose(archivo);
}

void leerArchivo(){
	lista_t *primero=NULL;
	lista_t *ultimo=NULL;
	lista_t *cursor=NULL;
	lista_t *auxiliar=NULL;

	FILE* archivo = fopen (CONTACTOS,"rb");
	if (!archivo){
		printf("Error en la apertura del archivo %s \n",CONTACTOS);
		return;
	}
	persona_t persona;
	fread(&persona,sizeof(persona),1,archivo);
	while(!feof(archivo)){
		if (persona.edad > 21){
			cargarLista(persona,&primero,&ultimo,&cursor,&auxiliar);
		}
		fread(&persona,sizeof(persona),1,archivo);
	}

	fclose(archivo);

	cargarArchivoOrdenado(&primero,&ultimo,&auxiliar);
}

void imprimirArchivoOrdenado(){
	FILE* archivo = fopen(CONTACTOS_ORD,"rb");
	persona_t persona;

	if (archivo == NULL){
		printf ("Error en la apertura del archivo %s, puede que no exista\n",CONTACTOS_ORD);
		return;
	}

	fread(&persona,sizeof(persona),1,archivo);
	while(!feof(archivo)){
		if (persona.edad > -1){
			imprimirPersona (persona);
		}
		fread(&persona,sizeof(persona),1,archivo);
	}
	fclose(archivo);
}

void ejercicio36(){

	int respuesta;

	do{
		printf("1)Cargar Lista\n0) Salir\n");
		scanf("%d",&respuesta);
		switch(respuesta){
		case 1:
			leerArchivo();
			imprimirArchivoOrdenado();
		break;
		}
		printf("\nDesea seguir ?\n1)SI 0)NO\n");
		scanf("%d",&respuesta);
	}while(respuesta);
}
