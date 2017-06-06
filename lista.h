#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>
#include <stdbool.h>


/* *****************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

struct lista;  // Definición completa en lista.c.
typedef struct lista lista_t;


/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/
// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t* lista_crear(void);

// Devuelve verdadero o falso, según si la lista tiene o no elementos enlistados.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t* lista);


// Agrega un nuevo elemento a la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al inicio
// de la lista.
bool lista_insertar_primero(lista_t* lista, void *dato);


// Agrega un nuevo elemento a la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al final
// de la lista.
bool lista_insertar_ultimo(lista_t* lista, void *dato);

// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void* lista_borrar_primero(lista_t* lista);


// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void* lista_ver_primero(const lista_t* lista);


// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void* lista_ver_ultimo(const lista_t* lista);


// Devuelve el tamaño de la lista, según la cantidad de elementos enlistados en la lista.
// Pre: la lista fue creada.
size_t lista_largo(const lista_t* lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
//Post: Se eliminaron todos los elementos de la lista
void lista_destruir(lista_t* lista, void destruir_dato(void*));


/* *****************************************************************
 *                    PRIMITIVAS DE ITERADORES
 * *****************************************************************/


typedef struct lista_iter lista_iter_t;


// Crea un iter.
//Pre:la lista fue creada
// Post: devuelve un nuevo iter vacío.
lista_iter_t* lista_iter_crear(lista_t *lista);

// Devuelve verdadero o falso, según si el iterador puede avanzar en la lista o se encuentre
// en el final y no pueda.
// Pre: el iter fue creado
bool lista_iter_avanzar(lista_iter_t* iter);

// Obtiene el valor del elemento en el que se encuentra el iterador. Si el actual tiene
// elementos, se devuelve el valor del actual, si no tiene valor devuelve NULL.
// Pre: el iterador fue creado.
// Post: se devolvió el elemento de la lista en donde se encontraba el iterado, cuando es valido.
void *lista_iter_ver_actual(const lista_iter_t* iter);

// Devuelve verdadero o falso, según si el iterador se encuentra o no en el final.
// Pre: el iter fue creado
bool lista_iter_al_final(const lista_iter_t* iter);

//Destruye el iterador
//Pre: El iterador fue creado
//Post: El iterador fue destruido
void lista_iter_destruir(lista_iter_t* iter);

// Agrega un nuevo elemento a la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al adelante del anterior
// y atras del actual de donde se encontraba el iterador, la lista tiene un elemento mas
bool lista_iter_insertar(lista_iter_t* iter, void* dato);

// Se quita el elemento en el que se encuentra el iterador de la lista. Si la lista tiene elementos o el actual no
// es un elemento,se devuelve su valor, si está vacía o el actual no es elemento de la lista, devuelve NULL.
// Pre: la lista fue creada, el iter fue creado.
// Post: se devolvió el valor del elemento borrado, la lista
// contiene un elemento menos, si la lista no estaba vacía o el iterador no se encontraba al final.
void* lista_iter_borrar(lista_iter_t* iter);

//Itera la lista con un iterador interno y recibe la funcion visitar mientras que esta es true
//continua iterando en caso contrario frena la iteracion
//Pre: Lista creada.
//Post: Se aplica funcion visitar a todos los datos, mientras que cada uno de true.
void lista_iterar(lista_t* lista, bool (*visitar)(void* dato, void* extra)  , void* extra);


void pruebas_lista_alumno(void);




#endif // LISTA_H
