/*
EJERCICIO 43:

El servicio técnico de CosmeFulanito recibe órdenes de trabajo diarias.
Las mismas son cargadas en un archivo secuencial por el personal de recepción bajo la siguiente
 estructura de datos:

typedef struct{
   long numeroDeOrden;
   char cliente[40];
   char descripciondeFalla[200];
   char modelo[65];
   char fecha[10];
   char hora[10];
}repuestos_t;
Se pide:

Hacer una pila con las órdenes de trabajo de forma tal que la más vieja sea la última en cargarse.
 */


#include "../../lib/compartida.h"

void pedirFecha(char* fecha){
	char dia [2];
	char mes [2];
	char anio [4];
	//dd/mm/aa
	do{
		printf("Ingrese el dia 1 a 31 \n");
		gets(dia);
		fflush(stdin);
	}while (31 < atoi(dia) || 1 > atoi(dia));

	if (dia[1] == '\0')
		strcat(fecha,"0");

	strcat (fecha,dia);

	strcat(fecha,"/");

	do{
		printf("Ingrese el mes 1 a 12 \n");
		gets(mes);
		fflush(stdin);
	}while (12 < atoi(mes) || 1 > atoi(mes));

	if (mes[1] == '\0')
		strcat(fecha,"0");
	strcat(fecha,mes);
	strcat(fecha,"/");

	do{
		printf("Ingrese el anio \n");
		gets(anio);
		fflush(stdin);
	}while (ANIO_ACTUAL < atoi(anio) || 1900 > atoi(anio));

	strcat(fecha,anio);
	fecha[8]='\0';
}

void pedirHora (char* hora){
	char horas [2];
	char minutos [2];

	do{
		printf("Ingrese la hora 0 a 23 \n");
		gets(horas);
		fflush(stdin);
	}while (23 < atoi(horas) || 0 > atoi(horas));

	if (horas[1] == '\0')
		strcat(hora,"0");

	strcat (hora,horas);

	strcat(hora,":");

	do{
		printf("Ingrese los minutos 0 a 59 \n");
		gets(minutos);
		fflush(stdin);
	}while (59 < atoi(minutos) || 0 > atoi(minutos));

	if (minutos[1] == '\0')
		strcat(hora,"0");
	strcat(hora,minutos);
	//hh:mm
	hora[5]='\0';

}

repuestos2_t pedirRepuesto2(){
	repuestos2_t producto;

	printf("Ingrese el numero de orden \n");
	scanf("%ld",&producto.numeroDeOrden);
	fflush(stdin);
	printf("Ingrese el cliente \n");
	gets(producto.cliente);
	fflush(stdin);
	printf("Ingrese la descripcion \n");
	gets(producto.descripciondeFalla);
	fflush(stdin);
	printf("Ingrese el modelo \n");
	gets(producto.modelo);
	fflush(stdin);

	pedirFecha(producto.fecha);
	pedirHora (producto.hora);

	return producto;

}



void ordenamientoOrdenes (listaRepuesto2_t** primero,listaRepuesto2_t** ultimo,	pilaRepuestos_t** primeroPila){

	//GENEERO UNA LISTA PARA A ORDENARLOS DE LA FECHA MAS NUEVA A LA MAS VIEJA
	//31/10/2020
	//30/10/2020
	listaRepuesto2_t* auxiliar=NULL;
	listaRepuesto2_t* cursor=NULL;

	auxiliar = (listaRepuesto2_t*)malloc (sizeof (listaRepuesto2_t));
	auxiliar->dato = pedirRepuesto2();

	if ((*primero)==NULL && (*ultimo)==NULL){ // lista vacia
		(*primero)=(*ultimo)=auxiliar;
		auxiliar->anterior = NULL;
		auxiliar->siguiente = NULL;
	}else{
		//BUSCO POSICION
		cursor = (*primero);
		while((cursor &&  (0 > strcmp((cursor->dato).fecha,(auxiliar->dato).fecha)) )||
				(cursor && (0 == strcmp((cursor->dato).fecha,(auxiliar->dato).fecha))
				&& (0 > strcmp((cursor->dato).hora,(auxiliar->dato).hora)))){//ORDENO ALFABETICAMENTE DESCRIPCION
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

}

void verPila(pilaRepuestos_t* primero){
	pilaRepuestos_t* aux;
	printf("N°ORDEN\t\tFECHA\t\tHORA\t  CLIENTE\t\tMODELO\t\t    DESCRIPCION\n");
	while(primero){ // no apunte a null, si apunta null la pila esta vacia
		aux=primero;
		printf("%-6ld\t\t%-10s\t%-10s%-20s  %-20s%-100s\n",aux->dato.numeroDeOrden,aux->dato.fecha,aux->dato.hora,aux->dato.cliente,aux->dato.modelo,aux->dato.descripciondeFalla);
		primero = primero->lazo;
		free(aux);
	}
}

void cargarPila(listaRepuesto2_t* primero,pilaRepuestos_t** primeroPila){
	//CARGO LA LISTA EN LA PILA
	listaRepuesto2_t* cursor = primero;
	listaRepuesto2_t* auxiliar;
	pilaRepuestos_t* auxPila = NULL;

	while(cursor){
		auxiliar= cursor;
		auxPila = (pilaRepuestos_t*) malloc (sizeof(pilaRepuestos_t));
		auxPila->dato = auxiliar->dato;
		if (!(*primeroPila)){//pila vacia
			auxPila->lazo = NULL;
			(*primeroPila)= auxPila;
		}else{
			auxPila->lazo = (*primeroPila);
			(*primeroPila) = auxPila;
		}
		cursor = cursor->siguiente;
		free(auxiliar);
	}
}

void ejercicio43(){
	char respuesta;
	listaRepuesto2_t* primero=NULL;
	listaRepuesto2_t* ultimo=NULL;
	pilaRepuestos_t* primeroPila = NULL;

	do{
		printf("1) Cargar ordenes \n");
		printf("S) Salir \n");
		scanf("%c",&respuesta);
		fflush(stdin);
		switch(respuesta){
		case '1':
			ordenamientoOrdenes(&primero,&ultimo,&primeroPila);
		break;
		case 's':
		case 'S':
			cargarPila(primero,&primeroPila);
			verPila(primeroPila);
		break;
		}
	}while (respuesta != 'S' && respuesta != 's');
}
