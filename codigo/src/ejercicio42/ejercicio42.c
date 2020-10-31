/*
EJERCICIO 42:

El proveedor de repuestos de CosmeFulanito informó que una partida de repuestos salió con falla y
 debe ser devuelta. Para identificar la partida, el proveedor indicó que la falla fue en el partNumber: 1234
 que tiene números de serie con el bit 3 y 5 en 1.

Para estas tareas se solicita:

Hacer una cola con todos los registros fallados
Realizar la baja física a todos los repuestos fallados
Crear un archivo donde se vuelque el contenido de la cola en orden inverso.
 */


#include "../../lib/compartida.h"

void aColarRepuesto (repuestos_t repuesto,colaFallados_t** primero,colaFallados_t** ultimo){

	colaFallados_t* auxiliar = (colaFallados_t*)malloc (sizeof (colaFallados_t));
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

void cargarArchivoFallados(colaFallados_t* ultimo,colaFallados_t* primero){
	FILE* archivo= fopen (STOCK_FALLO,"wb");
	colaFallados_t* auxiliar;
	if (!archivo){
		printf("Error en la creacion del archivo %s \n",STOCK_FALLO);
		return;
	}

	while(ultimo){
		auxiliar = ultimo;
		ultimo = ultimo->anterior;
		fwrite(&auxiliar->dato,sizeof(auxiliar->dato),1,archivo);
		free(auxiliar);
	};

	fclose(archivo);
}

void arreglarPartidaRepuestos(){
	FILE* archivo = fopen (STOCK,"rb");
	FILE* archivoNuevo = fopen (STOCKN,"wb");
	colaFallados_t* primero = NULL;
	colaFallados_t* ultimo = NULL;
	repuestos_t repuesto;

	if (!archivo){
		printf("Error en la apertura del archivo %s, puede que no exista \n",STOCK);
		return;
	}
	if (!archivoNuevo){
		printf("Error en la creacion del archivo %s \n",STOCKN);
	}

	fread(&repuesto,sizeof(repuesto),1,archivo);
	while(!feof(archivo)){
		if (repuesto.partNumber == 1234 && (repuesto.serialNumber & (1<<3)) && (repuesto.serialNumber & (1<<5))){
			aColarRepuesto (repuesto,&primero,&ultimo);
		}else{
			fwrite (&repuesto,sizeof(repuesto),1,archivoNuevo);
		}
		fread(&repuesto,sizeof(repuesto),1,archivo);
	}

	cargarArchivoFallados(ultimo,primero);
	fclose (archivo);
	fclose (archivoNuevo);
	remove (STOCK);
	rename (STOCKN,STOCK);

}

void verArchivoFalla(){
	FILE* archivo = fopen (STOCK_FALLO,"rb");
	if(!archivo){
		printf("Error apertura archivo %s, puede que no exista \n",STOCK_FALLO);
		return;
	}
	printf("N°PARTE\t\tN°SERIAL\t\tDESCRIPCION\t\tUBICACION\n");
	repuestos_t repuesto;
	fread(&repuesto,sizeof(repuesto),1,archivo);
	while(!feof(archivo)){
		printf("%-7ld\t\t%-8ld\t\t%-20s\t%-50s\n",repuesto.partNumber,repuesto.serialNumber,repuesto.descripcion,repuesto.ubicacion);
		fread(&repuesto,sizeof(repuesto),1,archivo);
	}
	fclose(archivo);
}

void ejercicio42(){
	char respuesta;
	do{
		printf("1) Arreglar fallas \n");
		printf("S) Salir \n");
		scanf("%c",&respuesta);
		fflush(stdin);
		switch(respuesta){
			case '1':
				arreglarPartidaRepuestos();
			break;
			case 's':
			case 'S':
				verArchivoFalla();
			break;
		}
	}while(respuesta != 'S' && respuesta != 's');
}
