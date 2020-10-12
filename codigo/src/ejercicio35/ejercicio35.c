/*
EJERCICIO 35:

Hacer un programa que tome los datos de contacto de una persona (Nombre, Apellido, edad, teléfono, mail) y
los cargue, en forma directa, en una pila de memoria dinámica. Imprimir en pantalla y cargar en un archivo
llamado "contactos.dat", de organización secuencial, los registros ingresados por el usuario si la persona
tiene una edad mayor a 21 años.
 */

#include "../../lib/ejercicio35.h"

int menu(){
	int respuesta;

	printf("1) Cargar persona \n");
	printf("2) Imprimir pila de personas \n");
	printf("3) Salir \n");
	scanf("%d",&respuesta);
	return respuesta;
}

persona_t pedirDatos(){
	persona_t persona;
	printf("Ingrese el nombre \n");
	scanf("%s",persona.nombre);
	printf("Ingrese el apellido \n");
	scanf("%s",persona.apellido);
	printf("Ingrese la edad \n");
	scanf("%d",&persona.edad);
	printf("Ingrese el telefono \n");
	scanf("%ld",&persona.telefono);
	printf("Ingrese el mail \n");
	scanf("%s",persona.mail);
	return persona;
}

void imprimirPersona (persona_t persona){
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

void imprimirPersonas(pila_t** auxiliar,pila_t** primero){
	while((*primero)){ // no apunte a null, si apunta null la pila esta vacia
		imprimirPersona((*primero)->dato);
		(*auxiliar)=(*primero);
		(*primero) = (*primero)->lazo;
		free((*auxiliar));
	}
}

void ejercicio35(){
	int respuesta;
	pila_t *auxiliar;
	pila_t *primero=NULL;

	do{
		respuesta=menu();
		switch(respuesta){
			case 1:
				cargarPersona(&auxiliar,&primero);
			break;
			case 2:
				imprimirPersonas(&auxiliar,&primero);
			break;
			case 3:
			break;
			default:
				printf("Ingrese una opcion valida \n");
			break;
		}
	}while (respuesta!=3);

}




