#ifndef BLOOM_H
#define BLOOM_H

#include <stdbool.h>
#include <stddef.h>


struct filter;
typedef struct filter filter_t;


//TDA COUNTING BLOOM


/* Crea el counting bloom filter
 */
typedef void (*filter_destruir_dato_t) (void*);

size_t filter_report(filter_t* filter,char* tag);


filter_t *filter_crear(size_t tam);


/* Destruye la estructura liberando la memoria pedida y llamando a la función
 * destruir para cada par (clave, dato).   /not sure yet
 * Pre: La estructura counting bloom filter fue inicializada
 * Post: La estructura counting bloom filter fue destruida
 */
void filter_destruir(filter_t *filter);

void filter_count(filter_t* filter,char* dato);


#endif //BLOOM_H