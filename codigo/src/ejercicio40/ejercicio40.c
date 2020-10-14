/*
EJERCICIO 40:

Utilizando el archivo “potencia.dat” creado en el Ejercicio 39, realizar una función que pase como parámetro,
 entre otros datos, la clave del registro (id).

La función ubicará el registro correspondiente al id pasado como parámetro, y
utilizando punteros imprimirá la primera palabra del campo "desc" en forma inversa, además cambiará el
estado del bit 3 para luego actualizar el archivo. Además, se agregará a una pila la potencia cuando los bits 0 y 2,
 del campo estado, estén encendidos, en caso contrario se agregará el registro al archivo “salida.dat” de
 organización secuencial.
 */

#include "../../lib/compartida.h"

potencia_t buscarRegistro(int id){
	FILE* archivo = fopen(POTENCIA,"rb+");
	potencia_t registro;
	//BUSQUEDA DE ARCHIVO DIRECTO
	registro.desc[0] = '-'; // REGISTRO NO ENCONTRADO O ERRONEO

	if (!archivo){
		printf("Error en la apertura del archivo %s puede que no exista \n",POTENCIA);
		registro.desc[0] = '*';//ERROR
		return registro;
	}

	fseek(archivo,(long)(id)*sizeof(registro),SEEK_SET);
	fread(&registro,sizeof(registro),1,archivo);

	fclose(archivo);
	return registro;
}

void invertirPalabra(char* primerPalabra){
	char auxiliar;
	int largo= strlen(primerPalabra);
	int j = largo-1;

	for(int i=0;i<largo/2;i++){
		auxiliar = *(primerPalabra+j);
		*(primerPalabra+j) = *(primerPalabra+i);
		*(primerPalabra+i) = auxiliar;
		j--;
	}
}

void actualizarArchivo(potencia_t registro,int id){
	FILE* archivo = fopen (POTENCIA,"rb+");
	if (!archivo){
		printf("Error en la apertura del archivo %s puede que no exista \n",POTENCIA);
	}
	fseek (archivo,(id+1)*(long)sizeof(registro),SEEK_SET);
	fseek(archivo,(-1L)*(long)sizeof(registro),SEEK_CUR);
	fwrite(&registro,sizeof(registro),1,archivo);
	fclose(archivo);
}

void aPilar (potencia_t registro,pilaPotencia_t** primero){
	pilaPotencia_t* auxiliar = (pilaPotencia_t*) malloc (sizeof(pilaPotencia_t));
	auxiliar->dato = registro;
	if (!(*primero)){//pila vacia
		auxiliar->lazo = NULL;
		(*primero)= auxiliar;
	}else{
		auxiliar->lazo = (*primero);
		(*primero) = auxiliar;
	}
}

void agregarArchivoSalida(potencia_t registro){
	FILE* archivo = fopen (SALIDA,"rb+");//ABRO EL ARCHIVO
	if(!archivo){
		archivo = fopen (SALIDA,"wb+");//SI NO EXISTE LO CREO
		if (!archivo){
			printf("Error en la creacion del archivo %s \n",SALIDA);
			return;
		}
	}
	potencia_t registroLeido;
	//ALTA DE ARCHIVO SECUENCIAL
	//VERIFICO QUE NO EXISTA LA CLAVE,EN ESTE CASO LA CLAVE ES EL NOMBRE Y APELLIDO DE LA PERSONA
	fread(&registroLeido,sizeof(registroLeido),1,archivo);
	while(!feof(archivo)){
		if (!strcmp(registroLeido.desc,registro.desc)){
			return;// SI YA EXISTE EN EL ARCHIVO NO LA CARGO
		}
		fread(&registroLeido,sizeof(registroLeido),1,archivo);
	}
	fwrite(&registro,sizeof(registro),1,archivo);
	fclose(archivo);
}

void cargarPilaPotencia(potencia_t registro,pilaPotencia_t** primero){
	if ((registro.estado & (1 << 0)) && (registro.estado  & (1 << 2))){
		aPilar(registro,primero);
	}else{
		agregarArchivoSalida(registro);
	}
}

void operarRegistro(potencia_t* registro,int id,pilaPotencia_t** primero){
	char primerPalabra[60];
	int i = 0;
	while(registro->desc[i] != ' ' && i<strlen(registro->desc)){
		primerPalabra[i] = registro->desc[i];
		i++;
	}
	primerPalabra[i+1]='\0';

	invertirPalabra(primerPalabra);
	strcat (primerPalabra," ");
	strcat (primerPalabra,(registro->desc)+i+1);
	strcpy(registro->desc,primerPalabra);
	toggleBit(registro->estado,3); //CAMBIO EL BIT 3
	actualizarArchivo(*registro,id);

    cargarPilaPotencia(*registro,primero);

}

void imprimirPotencia(potencia_t registro){
	printf ("%03d				%08d		%-60s\n",registro.potencia,registro.estado,registro.desc);
}

void atenderPila(pilaPotencia_t** primero){
	pilaPotencia_t* cursor= *primero;
	printf ("***LISTADO DE POTENCIAS***\n\n");
	printf ("POTENCIA			ESTADO			DESCRIPCION\n");
	printf ("--------------------------------------------------------------------------------------\n");

	while(cursor){ // no apunte a null, si apunta null la pila esta vacia
		imprimirPotencia(cursor->dato);
		cursor = cursor->lazo;
	}
}

void verArchivoSalida(){
	FILE* archivo = fopen (SALIDA,"rb");
	if(!archivo){
		printf("Error apertura archivo %s, puede que no exista \n",SALIDA);
	}
	potencia_t registro;
	printf ("***LISTADO DE POTENCIAS***\n\n");
	printf ("POTENCIA			ESTADO			DESCRIPCION\n");
	printf ("--------------------------------------------------------------------------------------\n");
	fread(&registro,sizeof(registro),1,archivo);
	while(!feof(archivo)){
		imprimirPotencia(registro);
		fread(&registro,sizeof(registro),1,archivo);
	}
	fclose(archivo);
}

void liberarMemoriaEjercicio40(pilaPotencia_t* primero){
	pilaPotencia_t* cursor;
	pilaPotencia_t* auxiliar;
	cursor = primero;
	while(cursor){
		auxiliar= cursor;
		cursor = cursor->lazo;
		free(auxiliar);
	}
}

void ejercicio40(){
	int respuesta;
	int id;
	potencia_t registro;
	pilaPotencia_t* primero=NULL;

	do{
		printf("1) Buscar registro por ID \n");
		printf("2) Atender pila de potencia\n");
		printf("3) Listar archivo de salida\n");
		printf("0) Salir \n");
		scanf("%d",&respuesta);
		switch(respuesta){
		case 1:
			do{
				do{
					printf("Ingrese el ID \n");
					scanf("%d",&id);
				}while (id <= 0);
				registro = buscarRegistro(id);
				if (registro.desc[0]=='-'){
					printf("Registro no encontrado \n");
				}else if (registro.desc[0]=='*'){
					return;
				}
			}while(registro.desc[0]=='-');

			operarRegistro(&registro,id,&primero);
		break;
		case 2:
			atenderPila(&primero);
		break;
		case 3:
			verArchivoSalida();
		break;
		}
	}while(respuesta!=0);
	liberarMemoriaEjercicio40(primero);
}
