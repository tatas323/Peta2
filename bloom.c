#include "bloom.h"
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAM_INICIAL 500
#define COEF_REDIM 4
#define NUMPRIMO 11



struct filter{
	size_t cantidad;
	size_t capacidad;
	void**tabla[1];
	filter_destruir_dato_t destruir_dato;
};

struct campo{
    char* clave;
    void* dato;
}typedef campo_t;

//Hashing num Primos
size_t funcion_hash(const char* s, size_t hash_capacidad){
    size_t hashval;
    for(hashval = 0; *s != '\0';s++)
        hashval = *s + NUMPRIMO * hashval;
    return hashval % hash_capacidad;
}

campo_t* crear_campo(const char * clave, void * dato){
    campo_t* campo = malloc(sizeof(campo_t));
    if(!campo)
        return NULL;
    campo -> clave = malloc(sizeof(const char)* strlen(clave)+1);//Crear copia de clave
    strcpy(campo->clave,clave);
    campo-> dato = dato;
    return campo;
}


bool tabla_crear(filter_t* filter){
	for(int c=0;c<2;c++){
    	filter->tabla[c] = malloc (sizeof(lista_t*)* filter->capacidad);
    	if(!filter->tabla[c]){
    	    free(filter);
    	    return  false;
    	}
    	for (int i = 0; i < filter->capacidad ; ++i) {
    	    filter->tabla[c][i]=lista_crear();
    	    if(!filter->tabla[c][i]){
    	        free(filter->tabla[c]);
    	        free(filter);
    	        return  false;
    	    }
    	}
    	
    }
    return true;
}



filter_t* filter_crear(filter_destruir_dato_t destruir_dato){
	filter_t* filter=malloc(sizeof(filter_t));
    if(!filter)
        return NULL;
    filter->capacidad= TAM_INICIAL;
    if(!tabla_crear(filter))
        return NULL;
    if(destruir_dato) 
    	filter->destruir_dato=destruir_dato;
    else 
    	filter->destruir=NULL;
    filter->cantidad=0;
    return filter;
}



void filter_destruir(filter_t* filter){//nose si vamos a usar campo pero por ahora lo dejo asi
	for (int c = 0; c < 2 ; c++){
    	for (int i = 0; i < filter->capacidad ; ++i) {
        	lista_iter_t* iter_lista = lista_iter_crear(filter->tabla[c][i]);
        	campo_t* campo=lista_iter_borrar(iter_lista);
        	while (campo){
            	if(filter->destruir_dato){
                	if(campo->dato)
                    	filter->destruir_dato(campo->dato);
            	}
            	free(campo->clave);
            	free(campo);
            	campo=lista_iter_borrar(iter_lista);
        	}
        	lista_iter_destruir(iter_lista);
        	lista_destruir(filter->tabla[c][i],free);

    	}
    	free(filter->tabla[c]);
    }
    free(filter);
}