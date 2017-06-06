#include "tweet.h"
#include "bloom.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/


 void procesar_tweets(int argc , char* argv[], long n,long k){
 	FILE* arch = fopen(argv[1],"r");
		if(!arch){
		fprintf(stderr, "//%s//No se pudo Abrir el archivo\n",argv[0] );
		return ;
	}
 }


void procesar_usuarios(int argc , char* argv[], long n,long k){
	FILE* arch = fopen(argv[1],"r");
		if(!arch){
		fprintf(stderr, "//%s//No se pudo Abrir el archivo\n",argv[0] );
		return ;
	}
}






 
int main(int argc , char* argv[], long n,long k){
 	if(argc!=3){
 		fprintf(stderr, "//%s//Numero incorrecto de argumentos\n",argv[0]);
 	}
 	
 }