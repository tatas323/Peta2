#ifndef TWEET_H
#define TWEET_H

#include <stdbool.h>
#include <stddef.h>


/*Recibe un txt con entrada:
Usuario,tag1,tag2,tag3...
Recibe dos enteros n = tamaño total ,y k = cantidad de tweets  (creo)
Imprime por salida estandar los tweets ordenados por ocurrencias*/
void procesar_tweets(int argc , char* argv[], long n,long k); //puede ser que necesitemos long el archivo pesa 450 mb


/*Usuario,tag1,tag2,tag3...
Recibe dos enteros n = tamaño total ,y k = cantidad de tweets  (seguro necesitamos esto tambien)
Imprime por salida estandar los usuarios y cantidad de hashtags que utilizaron ordenados segun cantidad de hashtags (mayor a menor) */
void procesar_usuarios(int argc , char* argv[], long n,long k);





#endif //TWEET_H
