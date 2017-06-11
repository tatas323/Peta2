#include "testing.h"
#include "lista.h"
#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAM_INICIAL 500
#define COEF_REDIM 4
#define COEF_REDIM_GUARD 2
#define NUMPRIMO 11

#include "lista.h"
/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/
struct hash{
    size_t cantidad;
    size_t tam;
    lista_t** tabla;
    hash_destruir_dato_t destruir;
};

struct hash_iter{
    size_t iterados;
    size_t posicion;
    const hash_t* hash;
    lista_iter_t* lista_iter;
};

struct campo{
    char* clave;
    void* dato;
}typedef campo_hash_t;




//FNVHash 

size_t funcion_hash(const char* s){
    size_t hashval;
    for(hashval = 0; *s != '\0';s++)
        hashval = (size_t)*s + NUMPRIMO * hashval;
    return hashval;
}

//Creo tabla del hash
bool tabla_crear(hash_t* hash){
    hash->tabla = malloc (sizeof(lista_t*)* hash->tam);
    if(!hash->tabla){
        free(hash);
        return  false;
    }
    for (int i = 0; i < hash->tam ; ++i) {
        hash->tabla[i]=lista_crear();
        if(!hash->tabla[i]){
            for (int j = 0; j < i; ++j) {
                lista_destruir(hash->tabla[j],NULL);
            }
            free(hash->tabla);
            free(hash);
            return  false;
        }
    }
    return true;
}

//Destruyo la tabla del hash
void tabla_destruir(hash_t* hash){
    for (int i = 0; i < hash->tam ; ++i) {
        campo_hash_t* campo=lista_borrar_primero(hash->tabla[i]);
        while (campo){
            if(hash->destruir){
                if(campo->dato)
                    hash->destruir(campo->dato);
            }
            free(campo->clave);
            free(campo);
            campo=lista_borrar_primero(hash->tabla[i]);
        }
        lista_destruir(hash->tabla[i],free);
    }
    free(hash->tabla);
}

//Redimensiono el tamaño del hash
bool hash_redimensionar(hash_t* hash, size_t n_tam){
    hash_t* auxiliar=malloc(sizeof(hash_t));
    if(!auxiliar) return false;
    auxiliar->tam= n_tam;
    if(!tabla_crear(auxiliar))
        return false;
    auxiliar->cantidad=0;
    auxiliar->destruir=hash->destruir;
    hash_iter_t* iter =hash_iter_crear(hash);
    if(!iter) return false;
    while (!hash_iter_al_final(iter)){
        campo_hash_t* campo = lista_iter_ver_actual(iter->lista_iter);
        if(!hash_guardar(auxiliar,campo->clave,campo->dato)){
            hash_iter_destruir(iter);
            hash_destruir(auxiliar);
            return false;
        }
        hash_iter_avanzar(iter);
    }
    hash_iter_destruir(iter);
    hash->destruir=NULL;
    tabla_destruir(hash);
    hash->destruir=auxiliar->destruir;
    hash->tam = auxiliar->tam;
    hash->tabla = auxiliar->tabla;
    hash->cantidad = auxiliar->cantidad;
    free(auxiliar);
    return true;
}

//Busco el campo en el hash
campo_hash_t* buscar_campo(const hash_t* hash,const char* clave){
    size_t pos_hash = funcion_hash(clave) % hash->tam;
    lista_iter_t* iter_lista =lista_iter_crear(hash->tabla[pos_hash]);
    campo_hash_t* campo = lista_iter_ver_actual(iter_lista);
    while(campo){
        if(!strcmp(campo->clave,clave)){
            free(iter_lista);
            return campo;
        }
        lista_iter_avanzar(iter_lista);
        campo = lista_iter_ver_actual(iter_lista);
    }
    free(iter_lista);
    return NULL;

}

//Creo campo
campo_hash_t* crear_campo(const char * clave, void * dato){
    campo_hash_t* campo = malloc(sizeof(campo_hash_t));
    if(!campo)
        return NULL;
    campo -> clave = malloc(sizeof(const char)* strlen(clave)+1);//Crear copia de clave
    strcpy(campo->clave,clave);
    campo-> dato = dato;
    return campo;
}


hash_t* hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t* hash=malloc(sizeof(hash_t));
    if(!hash)
        return NULL;
    hash->tam= TAM_INICIAL;
    if(!tabla_crear(hash))
        return NULL;
    if(destruir_dato) hash->destruir=destruir_dato;
    else hash->destruir=NULL;
    hash->cantidad=0;
    return hash;
}


bool hash_guardar(hash_t* hash, const char *clave, void *dato){
     if(hash->cantidad*COEF_REDIM_GUARD >= hash->tam)
        hash_redimensionar(hash,hash->tam*COEF_REDIM_GUARD);
    size_t pos_hash = funcion_hash(clave) % hash->tam;
    campo_hash_t* campo = buscar_campo(hash,clave);
    if(!campo){
        campo_hash_t* campo_nuevo = crear_campo(clave,dato);
        if(!campo_nuevo)
            return false;
        hash->cantidad++;
        return lista_insertar_ultimo(hash->tabla[pos_hash],campo_nuevo);
    }
    void* auxiliar=campo->dato;
    campo->dato=dato;
    if(hash->destruir)// Si es necesario destruir! Yo pense lo mismo, las pruebas dadas no liberan y pierdo 20 bytes!
        hash->destruir(auxiliar);
    return true;
}


void *hash_borrar(hash_t *hash, const char *clave){
    if(hash->tam /COEF_REDIM>=hash->cantidad && hash->tam>=TAM_INICIAL)
        hash_redimensionar(hash,hash->tam/COEF_REDIM);
    size_t pos_hash = funcion_hash(clave) % hash->tam;
    lista_iter_t* iter_lista = lista_iter_crear(hash->tabla[pos_hash]);
    campo_hash_t* campo = lista_iter_ver_actual(iter_lista);
    while(campo){
        if(!strcmp(campo->clave,clave)){
            campo_hash_t* auxiliar=lista_iter_borrar(iter_lista);
            void* dato  =auxiliar->dato;
            free(auxiliar->clave);
            free(auxiliar);
            hash->cantidad--;
            free(iter_lista);
            return dato;

        }

        lista_iter_avanzar(iter_lista);
        campo = lista_iter_ver_actual(iter_lista);
    }
    free(iter_lista);
    return NULL;
}

void* hash_obtener(const hash_t *hash, const char *clave){
    campo_hash_t* campo=buscar_campo(hash,clave);
    if(!campo)
        return NULL;
    return campo->dato;

}


bool hash_pertenece(const hash_t *hash, const char *clave){
   return buscar_campo(hash,clave);
}

size_t hash_cantidad(const hash_t *hash){
    return hash->cantidad;
}

void hash_destruir(hash_t* hash){
    tabla_destruir(hash);
    free(hash);
}

hash_iter_t *hash_iter_crear(const hash_t *hash){
    hash_iter_t* iter = malloc(sizeof(hash_iter_t));
    if(!iter)
        return NULL;
    iter->hash=hash;
    iter->posicion=0;
    iter->iterados=0;
    iter->lista_iter = lista_iter_crear(iter->hash->tabla[iter->posicion]);
    if(!hash_iter_ver_actual(iter)){
        hash_iter_avanzar(iter);
        iter->iterados=0;// se pone en 0 ya que avanzar sumaria un iterado.
    }
    return iter;
}

bool hash_iter_avanzar(hash_iter_t* iter){
    if(hash_iter_al_final(iter))
        return false;
    if(!iter->lista_iter)
        iter->lista_iter = lista_iter_crear(iter->hash->tabla[iter->posicion]);
    if(lista_iter_al_final(iter->lista_iter)){

        if(iter->posicion==iter->hash->tam -1){
            iter->iterados++;
            return true;
        }
        lista_iter_destruir(iter->lista_iter);
        iter->posicion++;
        iter->lista_iter = lista_iter_crear(iter->hash->tabla[iter->posicion]);
        if(hash_iter_ver_actual(iter)){
            iter->iterados++;
            return true;
        }
        return hash_iter_avanzar(iter);
    }
    lista_iter_avanzar(iter->lista_iter);
    if(!hash_iter_ver_actual(iter))
        return hash_iter_avanzar(iter);
    iter->iterados++;
    return true;
}

const char* hash_iter_ver_actual(const hash_iter_t *iter){
    campo_hash_t* campo=lista_iter_ver_actual(iter->lista_iter);
    if(!campo)
        return NULL;
    return campo->clave;
}

bool hash_iter_al_final(const hash_iter_t *iter){
    return iter->iterados == iter->hash->cantidad;
}

void hash_iter_destruir(hash_iter_t* iter){
    if(iter->lista_iter) lista_iter_destruir(iter->lista_iter);
    free(iter);
}