/*
EJERCICIO 35:

Hacer un programa que tome los datos de contacto de una persona (Nombre, Apellido, edad, teléfono, mail) y
los cargue, en forma directa, en una pila de memoria dinámica. Imprimir en pantalla y cargar en un archivo
llamado "contactos.dat", de organización secuencial, los registros ingresados por el usuario si la persona
tiene una edad mayor a 21 años.
 */

#include "../../lib/compartida.h"


persona_t pedirDatos(){
	persona_t persona;
	fflush(stdin);
	printf("Ingrese el nombre \n");
	scanf("%s",persona.nombre);
	fflush(stdin);
	printf("Ingrese el apellido \n");
	scanf("%s",persona.apellido);
	fflush(stdin);
	printf("Ingrese la edad \n");
	scanf("%d",&(persona.edad));
	fflush(stdin);
	printf("Ingrese el telefono \n");
	scanf("%ld",&(persona.telefono));
	fflush(stdin);
	printf("Ingrese el mail \n");
	scanf("%s",persona.mail);
	fflush(stdin);
	return persona;
}

void imprimirPersona (persona_t persona){
	printf("---------------------------------------------------------\n");
	printf ("Nombre: %s \n",persona.nombre);
	printf ("Apellido: %s \n",persona.apellido);
	printf("Edad: %d \n",persona.edad);
	printf("Telefono: %ld \n",persona.telefono);
	printf("Mail: %s \n",persona.mail);
}

void cargarPersona(pila_t** auxiliar,pila_t** primero){
	persona_t persona = pedirDatos();
	(*auxiliar) = (pila_t*) malloc (sizeof(pila_t));
	(*auxiliar)->dato = persona;
	if (!(*primero)){//pila vacia
		(*auxiliar)->lazo = NULL;
		(*primero)= (*auxiliar);
	}else{
		(*auxiliar)->lazo = (*primero);
		(*primero) = (*auxiliar);
	}
}

void cargarPersonaArchivo(persona_t persona){
	int archivoVacio = 0; // NO
	FILE* archivo = fopen (CONTACTOS,"rb+");//ABRO EL ARCHIVO
	if(!archivo){
		archivo = fopen (CONTACTOS,"wb+");//SI NO EXISTE LO CREO
		if (!archivo){
			printf("Error en la creacion del archivo %s \n",CONTACTOS);
			return;
		}
		archivoVacio = 1;//SI
	}
	if (archivoVacio == 0){
		//ALTA DE ARCHIVO SECUENCIAL
		//VERIFICO QUE NO EXISTA LA CLAVE,EN ESTE CASO LA CLAVE ES EL NOMBRE Y APELLIDO DE LA PERSONA
		persona_t personaCargada;
		fread(&personaCargada,sizeof(personaCargada),1,archivo);
		while(!feof(archivo)){
			if (!strcmp(personaCargada.nombre,persona.nombre) && !strcmp(personaCargada.apellido,persona.apellido)){
				return;// SI YA EXISTE EN EL ARCHIVO NO LA CARGO
			}
			fread(&personaCargada,sizeof(personaCargada),1,archivo);
		}
	}

	if(persona.edad > 21){
		fwrite(&persona,sizeof(persona),1,archivo);
	}
	fclose(archivo);
}

void imprimirPersonas(pila_t** auxiliar,pila_t** primero){
	while((*primero)){ // no apunte a null, si apunta null la pila esta vacia
		cargarPersonaArchivo((*primero)->dato);
		imprimirPersona((*primero)->dato);
		(*auxiliar)=(*primero);
		(*primero) = (*primero)->lazo;
		free((*auxiliar));
	}
}

void verArchivo(){
	FILE* archivo = fopen (CONTACTOS,"rb");
	if(!archivo){
		printf("Error apertura archivo %s, puede que no exista \n",CONTACTOS);
	}
	persona_t persona;
	fread(&persona,sizeof(persona),1,archivo);
	while(!feof(archivo)){
		imprimirPersona(persona);
		fread(&persona,sizeof(persona),1,archivo);
	}
	fclose(archivo);
}

void ejercicio35(){
	int respuesta;
	pila_t *auxiliar;
	pila_t *primero=NULL;
	do{
		do{
			cargarPersona(&auxiliar,&primero);
			printf("Desea seguir cargando personas ? \n1) SI\n0) SALIR\n");
			scanf("%d",&respuesta);
		}while(respuesta != 0);
		imprimirPersonas(&auxiliar,&primero);
		//verArchivo();
		printf("Desea seguir ?\n1)SI\n0)NO\n");
		scanf("%d",&respuesta);
	}while (respuesta!=0);

}




