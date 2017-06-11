#include "heap.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define TAM_INI 500
#define COEF_REDIM 4

struct heap {
    size_t cantidad;
    size_t tam;
    void** tabla;
    cmp_func_t cmp; 
};



bool heap_redim(heap_t *heap,size_t n_tam){
    heap->tam=n_tam;
    void* datos_nuevo = realloc(heap->tabla, sizeof(void*)*n_tam);
    if(!datos_nuevo)
        return false;
    heap->tabla=datos_nuevo;
    return true;
}


void swap(void** a, void** b){
    void* cambio = *a;
    *a = *b;
    *b = cambio;
}



heap_t *heap_crear(cmp_func_t cmp){
    heap_t *heap = malloc(sizeof(heap_t));
    if(!heap)
    	return NULL;
    heap->tabla = calloc(TAM_INI,sizeof(void*));
    if(!heap->tabla){
    	free(heap);
    	return NULL;
    }
    heap->tam = TAM_INI;
    heap->cantidad = 0;
    heap->cmp = cmp;
    return heap;
}


void upheap(void** tabla, size_t posicion,cmp_func_t cmp){
    if(posicion==0)
        return;
    size_t padre=(posicion-1)/2;
    if(cmp(tabla[posicion],tabla[padre])>0)
        swap(&tabla[padre],&tabla[posicion]);
    upheap(tabla, padre,cmp);
}



void downheap(void** tabla,size_t n, size_t posicion,cmp_func_t cmp){
    if(posicion>=n) return;
    size_t max=posicion;
    size_t hijo_izq=2*posicion + 1;
    size_t hijo_der=hijo_izq + 1;
    if(hijo_izq<n && cmp(tabla[hijo_izq],tabla[max])>0)
        max=hijo_izq;
    if(hijo_der<n && cmp(tabla[hijo_der],tabla[max])>0)
        max=hijo_der;
    if(max!=posicion){
        swap(&tabla[max],&tabla[posicion]);
        downheap(tabla,n,max,cmp);
    }
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
    for (int i = (int)cant; i>=0; i--)
            downheap(elementos, cant, (size_t)i, cmp);
    for (size_t final=cant; final-1>0; final--) {
        swap(&elementos[final-1], &elementos[0]);
        downheap(elementos, final-1,0, cmp);
    }
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
    heap_t *heap = malloc(sizeof(heap_t));
    if(!heap)
    	return NULL;
    heap->tabla = calloc(n,sizeof(void*));
    if(!heap->tabla){
    	free(heap);
    	return NULL;
    }
    heap->cantidad = 0;
    for(int tam = 0; tam<n ;tam++){
        heap->tabla[tam] = arreglo[tam];
        if(arreglo[tam])
            heap->cantidad++;
    }

    heap->tam = n;
    heap->cmp = cmp;
    heap_sort(heap->tabla,heap->cantidad,cmp);
    return heap;
}


void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	if(!heap_esta_vacio(heap)){
	    for(int c=0;c<heap->cantidad;c++){
		    if(destruir_elemento)
			    destruir_elemento(heap->tabla[c]);
        }
    }
	free(heap->tabla);
	free(heap);
}


size_t heap_cantidad(const heap_t *heap){
    return heap->cantidad;
}


bool heap_esta_vacio(const heap_t *heap){
    if(!heap)
        return false;
	return (!heap->cantidad);

}


bool heap_encolar(heap_t *heap, void *elem){
	if(!heap)
		return false;
    if(heap->cantidad*COEF_REDIM==heap->tam)
        if(!heap_redim(heap,heap->tam*COEF_REDIM))
            return false;
	heap->tabla[heap->cantidad] = elem;
    heap->cantidad++;
	upheap(heap->tabla,heap->cantidad-1,heap->cmp);
	return true;

}


void *heap_ver_max(const heap_t *heap){
    if (heap_esta_vacio(heap))
        return NULL;
    return heap->tabla[0];
}


void *heap_desencolar(heap_t *heap){
	if(heap_esta_vacio(heap))
		return NULL;
	void* desencolado = heap->tabla[0];
    heap->tabla[0]=heap->tabla[heap->cantidad-1];
    heap->tabla[heap->cantidad-1]= NULL;
    downheap(heap->tabla,heap->cantidad-1,0,heap->cmp);
    heap->cantidad--;

    if(COEF_REDIM*heap->cantidad==heap->tam)
        if(!heap_redim(heap,COEF_REDIM*heap->cantidad))
            return false;
	return desencolado;
}


