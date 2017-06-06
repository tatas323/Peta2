#ifndef BLOOM_H
#define BLOOM_H

#include <stdbool.h>
#include <stddef.h>


struct filter;
typedef struct filter filter_t;


//TDA COUNTING BLOOM


/* Crea el counting bloom filter
 */
filter_t *filter_crear(filter_destruir_dato_t destruir_dato);


/* Destruye la estructura liberando la memoria pedida y llamando a la función
 * destruir para cada par (clave, dato).   /not sure yet
 * Pre: La estructura counting bloom filter fue inicializada
 * Post: La estructura counting bloom filter fue destruida
 */
void filter_destruir(filter_t *filter);


#endif //BLOOM_H
