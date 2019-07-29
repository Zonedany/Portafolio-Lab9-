#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int insertar(char *,int tamanomax, int *tamanoactual,int *colision,int colisiones[]);
int hashing(char *,int tamanomax);
void Imprimir(int tamanomax);
void Informacion(int tamanomax,int tamano,int porutilizacion,int colision,int palabrasprocesadas, int colisiones[]);
int Buscar(char *, int tamanomax);

struct timespec start,finish;

struct nodo{
    char *dato;
    int ocupado;
}*cadena[150];

void CreaTablaHash(FILE *archivo, float porutilizacion){
  struct nodo aux1;
  int lon,tamano = 150,tamanomax,tamanoactual = 0,colision = 0,palabrasprocesadas = 0,opcion = 1;
  char aux[50],*valor;

  tamanomax = tamano * (porutilizacion / 100);

  int colisiones[tamanomax];

  for(int i = 0; i < tamanomax;i++){
    colisiones[i] = 0;
  }

  for(int i = 0; i < tamano; i++){
      cadena[i] = NULL;
  }

  while(!feof(archivo)){
    fscanf(archivo,"%s",aux);
    palabrasprocesadas++;
    lon = strlen(aux);
    valor = (char*)malloc(sizeof(char) * lon);
    strcpy(valor,aux);
    insertar(valor,tamanomax,&tamanoactual,&colision,colisiones);
    if(insertar(valor,tamanomax,&tamanoactual,&colision,colisiones) == -1){
      break;
    }
  }

  Imprimir(tamanomax);

  while(opcion == 1){
    printf("\n\nIngrese la palabra que desea buscar: ");
    scanf("%s",aux);
    Buscar(aux,tamanomax);
    printf("Tiempo de busqueda: %ld\n",(finish.tv_nsec-start.tv_nsec));
    printf("Desea buscar otra palabra: \n\n1. Si\n2. No");
    scanf("%i",&opcion);
  }

  Informacion(tamanomax,tamano,porutilizacion,colision,palabrasprocesadas,colisiones);

}

int insertar(char *valor, int tamanomax,int *tamanoactual,int *colision,int colisiones[]){
    int i = 0;
    struct nodo *NuevoNodo =(struct nodo*) malloc(sizeof(struct nodo));
    NuevoNodo->dato = valor;
    NuevoNodo->ocupado = 1;

    int llave = hashing(valor,tamanomax);

    if(cadena[llave] == NULL){
        cadena[llave] = NuevoNodo;
        *tamanoactual = *tamanoactual + 1;
    }
    else{
        if(tamanomax == *tamanoactual){
          printf("\n\nLa lista esta llena");
          return -1;
        }
        else{
          *colision = *colision + 1;
          colisiones[*tamanoactual] = colisiones[*tamanoactual] + 1;
          for(i = 0; i < tamanomax; i++){
            if(cadena[i] != NULL){
              cadena[i] = NuevoNodo;
              *tamanoactual++;
              return 1;
            }
          }
        }
      }
}

int hashing(char *cad,int tamanomax){
   int valor;
   char *c;

    for (c=cad;*c;c++){
      valor+=(int)(*c);
    }

    return(valor%tamanomax);
}

int Buscar(char *valor,int tamanomax){
    int llave = hashing(valor,tamanomax);

    clock_gettime(CLOCK_REALTIME, &start);
    if(strcmp(cadena[llave]->dato,valor)){
      clock_gettime(CLOCK_REALTIME, &finish);
      printf("Valor encontrado");
      return 1;
    }else{
      for(int i = 0; i < tamanomax; i++){
        if(strcmp(cadena[i]->dato,valor)){
          clock_gettime(CLOCK_REALTIME, &finish);
          printf("Valor encontrado");
          return 1;
        }
      }
    }

}

void Imprimir(int tamanomax){
    int i;

    for(int i = 0; i < tamanomax; i++){
      printf("\n%s",cadena[i]->dato);
    }

}

void Informacion(int tamanomax,int tamano,int porutilizacion,int colision,int palabrasprocesadas, int colisiones[]){
  int promediocolisiones = 0;

  for(int i = 0; i < tamanomax; i++){
    promediocolisiones = promediocolisiones + colisiones[i];
  }

  promediocolisiones = promediocolisiones / tamanomax;

  printf("\n\nEn total se procesaron %i palabras",palabrasprocesadas);

  printf("\n\nEl tamano total de la tabla era de %i palabras, pero su maximo de utilizacion eran %i",tamano,tamanomax);

  printf("\n\nEl numero maximo de colisiones fue de %i, el promedio de colisiones fue %i",colision,promediocolisiones);

}
