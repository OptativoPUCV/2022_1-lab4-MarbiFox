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
    
    //Variable auxiliar para mantener el arreglo anterior
    int oldSize = map->size;
    Pair ** auxBuckets = (Pair**) malloc (oldSize * sizeof(Pair*));
    

    //Aumentar Capacidad
    map->capacity = 2 * map->capacity;

    //Guardar el arreglo anterior en la variable auxiliar.
    for (int i = 0; i < oldSize; i++) {
        auxBuckets[i] = map->buckets[i];
    }

    //Crear un arreglo nuevo para el mapa
    map->buckets = (Pair**) malloc (map->capacity * sizeof(Pair*));

    //Inicializar nuevamente el size.
    map->size = 0;

    //Insertar los elementos en el nuevo arreglo.
    for (map->size = 0; map->size < oldSize; map->size++)
      {
        insertMap(map, auxBuckets[map->size]->key, auxBuckets[map->size]->value);
      }
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
    long pos = hash(key, map->capacity);

    //Verificar si la casilla ya fue borrada.
    if (map->buckets[pos]->key == NULL) return;
    
    //Recorrer el arreglo en busca de la clave.
    while(map->buckets[pos] != NULL) {
      //Si las claves coinciden, eliminar el dato.
      if (is_equal(key, map->buckets[pos]->key) == 1) {
        map->buckets[pos]->key = NULL;
        map->size--;
        return;
      }
      //Si no, seguir recorriendo.
      pos = (pos+1) % map->capacity;
    }
    
    // Si la clave no está, retornar vacío.
    return;
}

Pair * searchMap(HashMap * map,  char * key) {   
    //Buscar la clave a borrar.
    long pos = hash(key, map->capacity);

    //Verificar si la casilla existe.
    if (map->buckets[pos]->key == NULL) return NULL;
    
    //Recorrer el arreglo en busca de la clave.
    while(map->buckets[pos] != NULL) {
      //Si las claves coinciden, eliminar el dato.
      if (is_equal(key, map->buckets[pos]->key) == 1) {
        map->current = pos;
        return map->buckets[pos];
      }
      //Si no, seguir recorriendo.
      pos = (pos+1) % map->capacity;
    }
    
    // Si la clave no está, retornar NULL.
    return NULL;
}

Pair * firstMap(HashMap * map) {
    //Buscar el primer bucket válido.
    for (int i = 0; i < map->capacity; i++)
      {
        if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) {
          Pair * first = (Pair *) malloc (sizeof(Pair));
          first = map->buckets[i];
          map->current = i;
          return first;
        }
      }
  
    //Si no encuentra nada, retornar NULL.
    return NULL;
}

Pair * nextMap(HashMap * map) {
    //Buscar el current bucket válido.
    if (map->buckets[map->current+1] != NULL && map->buckets[map->current+1]->key != NULL) {
      return map->buckets[map->current+1];
    }
    
    return NULL;
}
