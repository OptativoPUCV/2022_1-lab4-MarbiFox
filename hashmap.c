#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    //Sacar la posición del arreglo
    int pos = hash(key, map->capacity);

    //Declarar variable aux
    Pair * aux = (Pair *) malloc (sizeof(Pair));
    aux = createPair(key, value);
    
    //Verificar si la casilla está ocupada.
    while(map->buckets[pos] != NULL && map->buckets[pos]->key != key) {
      //Recorrer el arreglo en busca de una casilla nula.
      if (is_equal(key, map->buckets[pos]->key) == 1) return;
      pos = (pos+1) % map->capacity;
    }

    //Verificar si hay espacio
    if (map->size >= 0.75*(map->capacity)) {
      enlarge(map);
    }
  
    //Colocar el elemento aux en el arreglo
    map->buckets[pos] = aux;
    map->size++;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)

    //Crear un mapa Auxiliar.
    int newCapac = (int) map->capacity * 2;
    HashMap * auxMap = createMap(newCapac);

    //Insertar los elementos del mapa anterior en el nuevo.
    
}


HashMap * createMap(long capacity) {
    //Reservar Memoria.
    HashMap * newMap = (HashMap *) malloc (sizeof(HashMap));
    //Definir capacidad
    newMap->capacity = capacity;
    //Crear Arreglo de Pairs.
    Pair ** hashElem = (Pair**) malloc (capacity*sizeof(Pair*));
    newMap->buckets = hashElem;
    //Asignar 0 a los valores iniciales.
    newMap->current = -1;
    newMap->size = 0;
    //Retornar el Mapa.
    return newMap;
}

void eraseMap(HashMap * map,  char * key) {    
    //Buscar la clave a borrar.
    long clave = hash(key, map->capacity);



    //Verificar si la casilla está ocupada.
    while(map->buckets[clave] != NULL && map->buckets[clave]->key != key) {
      //Recorrer el arreglo en busca de una casilla nula.
      if (is_equal(key, map->buckets[clave]->key) == 1) return;
      clave = (clave+1) % map->capacity;
    }

    //Eliminar directamente (Borrar Clave)
    map->buckets[clave]->key = NULL;
}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
