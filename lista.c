#include "lista.h"
#include <stdlib.h>
#include <stdio.h>


struct nodo{
	void* dato;
	struct nodo* siguiente;
}typedef nodo_t;

struct lista{
	nodo_t* primero;
	nodo_t* ultimo;
	size_t cantidad;
};

struct lista_iter{
    nodo_t* actual;
    nodo_t* anterior;
    lista_t* lista;
};

nodo_t* nodo_crear();

/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

lista_t* lista_crear(){
    lista_t* lista = malloc(sizeof(lista_t));
    if(lista == NULL) return NULL;
    lista->ultimo = NULL;
    lista->primero = NULL;
    lista->cantidad = 0;
    return lista;
}

bool lista_esta_vacia(const lista_t* lista){
	return (!lista->primero);
}

bool lista_insertar_primero(lista_t* lista, void *dato){
    nodo_t* nodo = nodo_crear();
    if(nodo==NULL) return false;
    nodo->dato = dato;
    nodo->siguiente=lista->primero;
    if(lista->primero == NULL){
        lista->ultimo = nodo;
    }
    lista->primero=nodo;
    lista->cantidad++;
    return true;
}

nodo_t* nodo_crear(){
    nodo_t* nodo = malloc(sizeof(nodo_t));
    nodo->siguiente=NULL;
    return nodo;
}

bool lista_insertar_ultimo(lista_t *lista, void* dato){

    nodo_t* nodo=nodo_crear();
    if(nodo==NULL) return false;
    nodo->dato = dato;
    if(lista->ultimo == NULL){
        lista->primero = nodo;
    }else{
        lista->ultimo->siguiente= nodo;
    }
    lista->ultimo= nodo;
    lista->cantidad++;
    return true;
}

void* lista_borrar_primero(lista_t *lista){
    if(lista->primero==NULL) return NULL;
    nodo_t* auxiliar = lista->primero;
    lista->primero=lista->primero->siguiente;
    if(lista->primero==NULL) lista->ultimo=NULL;
    void* dato = auxiliar->dato;
    free(auxiliar);
    lista->cantidad--;
    return dato;
}

void* lista_ver_primero(const lista_t *lista){
	if(lista_esta_vacia(lista)) return NULL;
	return lista->primero->dato;
}

void* lista_ver_ultimo(const lista_t* lista){
	if(lista_esta_vacia(lista)) return NULL;
	return lista->ultimo->dato;
}

size_t lista_largo(const lista_t *lista){
	return lista->cantidad;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)){
    while(lista->primero){
        void* dato = lista_borrar_primero(lista);
        if(destruir_dato) destruir_dato(dato);
    }
    free(lista);
}


/* *****************************************************************
 *                    PRIMITIVAS DE ITERADORES
 * *****************************************************************/

lista_iter_t* lista_iter_crear(lista_t* lista){
    lista_iter_t* iter = malloc(sizeof(lista_iter_t));
    iter->lista=lista;
    iter->actual=lista->primero;
    iter->anterior=NULL;
    return iter;
}

bool lista_iter_avanzar(lista_iter_t* iter){
    if(iter->actual==NULL) return false;
    iter->anterior=iter->actual;
    iter->actual=iter->anterior->siguiente;
    return true;
}

void* lista_iter_ver_actual(const lista_iter_t* iter){
    if(iter->actual==NULL) return NULL;
    return iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t* iter){
    if(iter->anterior == iter->lista->ultimo) return true;
    return false;
}

void lista_iter_destruir(lista_iter_t* iter){
    free(iter);
}

bool lista_iter_insertar(lista_iter_t* iter, void* dato){
    nodo_t* nodo = nodo_crear();
    if(nodo==NULL) return false;
    nodo->dato = dato;
    nodo->siguiente = iter->actual;
    if(iter->actual==NULL)iter->lista->ultimo=nodo;
    if(iter->anterior==NULL) iter->lista->primero=nodo;
    if(iter->anterior!=NULL) iter->anterior->siguiente=nodo;
    iter->actual=nodo;
    iter->lista->cantidad++;
    return true;
}

void* lista_iter_borrar(lista_iter_t* iter){
    if(iter->actual==NULL) return NULL;
    nodo_t* auxiliar = iter->actual;
    void* dato = auxiliar->dato;
    iter->actual=iter->actual->siguiente;
    if(iter->anterior==NULL) iter->lista->primero=iter->actual;
    if(iter->anterior!=NULL) iter->anterior->siguiente=iter->actual;
    if(iter->actual==NULL) iter->lista->ultimo = iter->anterior;

    free(auxiliar);
    iter->lista->cantidad--;
    return dato;
}


//ni idea donde definirla
void lista_iterar(lista_t* lista, bool (*visitar)(void* dato, void* extra)  , void* extra) {
    if(lista->primero==NULL) return;
    nodo_t* nodo = lista->primero;
    if (visitar) {
        while (nodo && visitar(nodo->dato, extra)) {
            nodo = nodo->siguiente;
        }
    }
}
