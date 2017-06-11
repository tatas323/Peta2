#include "bloom.h"
#include "lista.h"
#include "vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAM_INICIAL 500
#define COEF_REDIM 4
#define NUMPRIMO 11



struct filter{
    vector_t* tabla[2];
    size_t tam_vects;
};

//Hashing num Primos falta el % cuando sale de acax
size_t funcion_hash1(const char* s){
    size_t hashval;
    for(hashval = 0; *s != '\0';s++)
        hashval = (size_t)*s + NUMPRIMO * hashval;
    return hashval;
}

size_t funcion_hash2(const char *s, size_t len){
    size_t i=0;
    size_t hash=0;
    while(i!=len){
        hash+=s[i++];
        hash+=hash<<10;
        hash^=hash<<6;
    }
    hash+=hash<<3;
    hash^=hash<<15;
    return hash;
}

bool tabla_crear_bloom(filter_t* filter, size_t tam){
    for(int i=0;i<2;i++){
        filter->tabla[i] =vector_crear(tam);
        if(!filter->tabla[i])
            return false;
    }
    return true;
}

void filter_count(filter_t* filter,char* tag){//arregla para que no repita codigo
    size_t pos1=funcion_hash1(tag) % filter->tam_vects;
    size_t pos2=funcion_hash2(tag,strlen(tag)) % filter->tam_vects;
    //size_t pos=funcion_hash_bloom(dato) % filter->tam_vects;
    vector_sumar(filter->tabla[0],pos1,1);
    vector_sumar(filter->tabla[1],pos2,1);
    //vector_sumar(filter->tabla[2],pos2,1);
}

size_t filter_report(filter_t* filter,char* tag){
    size_t pos[2];
    pos[0]=funcion_hash1(tag) % filter->tam_vects;
    pos[1]=funcion_hash2(tag,strlen(tag)) % filter->tam_vects;
    //size_t pos=funcion_hash_bloom(dato) % filter->tam_vects;
    size_t min= (size_t) vector_obtener(filter->tabla[0], pos[0]);
    for (size_t i = 1; i <2 ; ++i) {//3
        if(vector_obtener(filter->tabla[i],pos[i])>min) {
            min = (size_t) vector_obtener(filter->tabla[i], pos[i]);
            //vector=i;
        }
    }
    return min;
}

filter_t* filter_crear(size_t tam){
    filter_t* filter=malloc(sizeof(filter_t));
    if(!filter)
        return NULL;
    if(!tabla_crear_bloom(filter,tam)){
        free(filter);
        return NULL;
    }
    filter->tam_vects=tam;
    return filter;
}



void filter_destruir(filter_t* filter){
    for(size_t i=0; i<2;i++){
        vector_destruir(filter->tabla[i]);
    }
    free(filter);
}