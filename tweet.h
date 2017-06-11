#ifndef TWEET_H
#define TWEET_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>


/*Recibe un txt con entrada:
Usuario,tag1,tag2,tag3...
Recibe dos enteros n = tamaño total ,y k = cantidad de tweets  (creoz que necesitemos long el archivo pesa 450 mb*/


/*Usuario,tag1,tag2,tag3...
Recibe dos enteros n = tamaño total ,y k = cantidad de tweets  (seguro necesitamos esto tambien)
Imprime por salida estandar los usuarios y cantidad de hashtags que utilizaron ordenados segun cantidad de hashtags (mayor a menor) */
int procesar_usuarios(FILE* arch, size_t n,size_t k);

int procesar_tweets(FILE* arch,size_t n, size_t k);






#endif //TWEET_H