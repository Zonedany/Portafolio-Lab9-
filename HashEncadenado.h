#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 100

struct nodo{
    char *dato;
    struct nodo *sgte;
};

void Crear_Tabla_Hash(struct nodo *cadena[],FILE *archivo);
int Leer_Archivo(struct nodo *cadena[],FILE *archivo);
int Hashing(char *cadena);
void Insertar_en_Tabla(struct nodo *cadena[0],char *valor);

void Crear_Tabla_Hash(struct nodo *cadena[], FILE *archivo){
		
	int i;
	for(i = 0; i < size; i++){
    	cadena[i] = NULL;
	}
	
}

int Leer_Archivo(struct nodo *cadena[],FILE *archivo){
	char aux[24];
	
	while( !feof(archivo) ){
		fscanf(archivo,"%s",aux);
		
		char *valor = (char*)malloc(sizeof(char) * strlen(aux));
		
		strcpy(valor,aux);
		Insertar_en_Tabla(cadena,valor);
	}
}

int Hashing(char *cadena){
	int valor;
	
	char *c;
    for(c = cadena,valor = 0; *c ;c++){
    	valor+=(int)(*c);
    }
    
    return(valor%size);
}

void Insertar_en_Tabla(struct nodo *cadena[],char *palabra){
    struct nodo *NuevoNodo = (struct nodo*)malloc(sizeof(struct nodo));
    
	NuevoNodo->dato = palabra;
    NuevoNodo->sgte = NULL;

    int clave = Hashing(palabra);

    if(cadena[clave] == NULL){
		cadena[clave] = NuevoNodo;
	}
	else{
        struct nodo *tmp = cadena[clave];
        
		while(tmp->sgte){
            tmp = tmp->sgte;
        }
        tmp->sgte = NuevoNodo;
    }
}

void TamanoListas(struct nodo *cadena[]){
	int i = 0,j = 0;
	int tamanomax = 0, tamanomin = 10000000,posmin,posmax,cantidadpalabras = 0;
	float promedio = 0;

	for(i = 0; i < size; i++){
    	j = 0;
    	struct nodo *tmp = cadena[i];
    	while(tmp){
        	cantidadpalabras++;
        	j++;
        	tmp = tmp->sgte;
    	}

    	if(j > tamanomax){
    		tamanomax = j;
        	posmax = i;
    	}
		else if(j < tamanomin){
    		tamanomin = j;
    		posmin = i;
    	}
    	
		promedio = promedio + j;
	}

	promedio = promedio/size;
	printf("El promedio de las listas es %f\n\nEl tamano min de datos en las listas es %i en la posicion %i\n\nEl tamano maximo de datos en las listas es %i en la posicion %i\n\nEl tamano total de palabras leidas es de %i",promedio,tamanomin,posmin,tamanomax,posmax,cantidadpalabras);

}

int Buscar_en_Tabla(struct nodo *cadena[],char *palabra){
    int clave = Hashing(palabra);
    
	struct nodo *tmp = cadena[clave];
    
	while(tmp){
        
		if(tmp->dato == palabra){
			printf("Encontrado: %s en cadena[%d]",palabra,clave);
            return 1;
        }
        tmp = tmp->sgte;
    }
    return 0;
}

void Imprimir_Tabla_Hash(struct nodo *cadena[]){
    int i;

    for(i = 0; i < size; i++){
        struct nodo *tmp = cadena[i];
        printf("cadena[%d]-->",i);
        
		while(tmp){
            printf("%s -->",tmp->dato);
            tmp = tmp->sgte;
        }
        printf("NULL\n");
    }
}
