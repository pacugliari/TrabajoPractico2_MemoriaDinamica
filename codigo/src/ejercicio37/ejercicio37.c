/*
EJERCICIO 37:

Existe un archivo llamado "datos.dat", de tipo binario, cuya organización es secuencial.
 Los datos están organizados según la siguiente estructura:

struct d{
long clave; //Clave o Id del registro

char d[30]; // Descripcion
unsigned char tipo; //Tipo de datos como entero sin signo
char b; //'A':Alta 'B':Baja
}
Se Pide: Realizar una funciún que pase como parámetro la clave, entre otros parámetros,
 y apile dos valores, la Clave y su posición física respecto al archivo (registro 1, 2, etc),
  si es que el campo tipo tiene el bit 4 con valor 1. En caso de no encontrarlo mostrar por pantalla
  "Registro no encontrado". La función debe devolver el puntero de pila. Realizar el main con varias
  llamadas a dicha función y proceder a mostrar las descripciones del archivo, mediante la pila como acceso directo,
   NO USAR VARIABLES GLOBALES.
 */

#include "../../lib/compartida.h"

void cargarDatos(){
	FILE* archivo = fopen (DATOS,"rb+");
	if(!archivo){
		archivo = fopen (DATOS,"wb+");
		if(!archivo){
			printf("Error en la apertura/creacion del archivo %s",DATOS);
			return;
		}
	}
	datos_t dato;
	printf("Ingrese la clave o id del registro \n");
	scanf("%ld",&(dato.clave));

	//BUSCO SI EXISTE LA CLAVE A DAR DE ALTA EN EL ARCHIVO
	datos_t registro;
	fread(&registro,sizeof(registro),1,archivo);
	while(!feof(archivo)){
		if (registro.clave == dato.clave){
			if (registro.b == 'B'){
				printf("El registro existe pero se encuentra dado de baja \n");
			}else if (registro.b == 'A'){
				printf("El registro ya existe \n");

			}
			return;
		}
		fread(&registro,sizeof(registro),1,archivo);
	}

	printf("Ingrese la descripcion \n");
	fflush(stdin);
	gets(dato.d);
	fflush(stdin);
	//scanf("%s",dato.d);
	int tipo;
	do{
		printf("Ingrese tipo de dato como entero sin signo (valor de 0 a 255) \n");
		scanf("%d",&tipo);
	}while(tipo > 255 || tipo < 0);
	dato.tipo = (unsigned char)(tipo); // convierto int a char
	dato.b = 'A';
	fwrite (&dato,sizeof(dato),1,archivo);
	fclose(archivo);
}

void imprimirDato(datos_t dato){
	printf ("%08ld		0x%-4X			%-30s\n",dato.clave,dato.tipo,dato.d);
}

void listarArchivo(){
	FILE* archivo = fopen (DATOS,"rb");
	datos_t registro;
	if(!archivo){
		printf("Error en la apertura del archivo %s",DATOS);
		return;
	}

	printf ("***LISTADO DE DATOS***\n\n");
		printf ("CLAVE			TIPO			DESCRIPCION\n");
		printf ("--------------------------------------------------------------------------------------\n");
	fread(&registro,sizeof(registro),1,archivo);
	while(!feof(archivo)){
			if (registro.b == 'A'){
				imprimirDato(registro);
			}
		fread(&registro,sizeof(registro),1,archivo);
	}
	fclose(archivo);
}

datos_t buscarDato(long clave,int* posicion){
	FILE* archivo = fopen (DATOS,"rb");
	datos_t registro;
	(*posicion) = 1;
	if(!archivo){
		printf("Error en la apertura del archivo %s",DATOS);
		registro.b = 'E'; //ERROR
		return registro;
	}

	fread(&registro,sizeof(registro),1,archivo);
	while(!feof(archivo)){
			if (clave == registro.clave && registro.b == 'A'){
				return registro;
			}
		fread(&registro,sizeof(registro),1,archivo);
		(*posicion)++;
	}
	registro.b = 'N'; // NO ENCONTRADO
	return registro;
	fclose(archivo);
}

pila2_t* apilar (long clave,pila2_t** primero){
	pila2_t* auxiliar=NULL;
	nodo_t nodo;
	datos_t dato = buscarDato(clave,&(nodo.posicion));
	nodo.clave = dato.clave;

	if ((dato.tipo & (1 << 3)) && dato.b == 'A'){ //VERIFICO BIT 4
		auxiliar = (pila2_t*) malloc (sizeof(pila2_t));
		auxiliar->dato = nodo;
		if (!(*primero)){//pila vacia
			auxiliar->lazo = NULL;
			(*primero)= auxiliar;
		}else{
			auxiliar->lazo = (*primero);
			(*primero) = auxiliar;
		}
	}else{
		printf("Registro no encotnrado \n");
	}


	return (*primero);
}

void obtenerDescripciones(pila2_t** primero){
	printf ("***LISTADO DE DATOS***\n\n");
	printf ("CLAVE			TIPO			DESCRIPCION\n");
	printf ("--------------------------------------------------------------------------------------\n");
	pila2_t* auxiliar = NULL;
	datos_t dato;
	while((*primero)){ // no apunte a null, si apunta null la pila esta vacia
		dato = buscarDato((*primero)->dato.clave,&((*primero)->dato.posicion));
		imprimirDato (dato);
		auxiliar=(*primero);
		(*primero) = (*primero)->lazo;
		free(auxiliar);
	}
}

void ejercicio37(){
	int respuesta;
	long clave;
	pila2_t* pila;
	pila2_t* primero=NULL;
	do{
		printf("1) CARGAR DATOS AL ARCHIVO \n");
		printf("2) REALIZAR LLAMADAS A FUNCION \n");
		printf("3) VER DATOS DEL ARCHIVO \n");
		printf("4) OBTENER DESCRIPCIONES \n");
		printf("0) SALIR \n");
		scanf("%d",&respuesta);
		switch(respuesta){
			case 1:
				cargarDatos();
			break;
			case 2:
				printf("Ingrese la clave a apilar \n");
				scanf("%ld",&clave);
				pila = apilar(clave,&primero);
			break;
			case 3:
				listarArchivo();
			break;
			case 4:
				obtenerDescripciones(&pila);
			break;
		}
	}while(respuesta!=0);
}


