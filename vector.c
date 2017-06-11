#include "vector.h"


// Funciones del alumno.

void vector_destruir(vector_t* vector){
    free(vector->datos);
    free(vector);
}


int vector_obtener(vector_t* vector, size_t pos){
    if(pos< vector->tam){
        return vector->datos[pos];
    }
    return 0;
}

bool vector_guardar(vector_t* vector, size_t pos, int valor){
    if(pos< vector->tam){
        vector->datos[pos]=valor;
        return true;
    }
    return false;
}

size_t vector_obtener_tamanio(vector_t* vector){
    return vector->tam;
}

// Funciones implementadas por la catedra.

vector_t* vector_crear(size_t tam) {
    vector_t* vector = malloc(sizeof(vector_t));

    if (vector == NULL) {
        return NULL;
    }
    vector->datos = calloc(tam , sizeof(int));

    if (tam > 0 && vector->datos == NULL) {
        free(vector);
        return NULL;
    }
    vector->tam = tam;
    return vector;
}

bool vector_sumar(vector_t* vector, size_t pos, int valor){
    if(pos>vector->tam)return false;
    if(!vector->datos[pos])
        vector->datos[pos]=valor;
    else
        vector->datos[pos]=vector->datos[pos]+valor;
    return true;
}

bool vector_redimensionar(vector_t* vector, size_t tam_nuevo) {
    int* datos_nuevo = realloc(vector->datos, tam_nuevo * sizeof(int));

    // Cuando tam_nuevo es 0, es correcto si se devuelve NULL.
    // En toda otra situación significa que falló el realloc.
    if (tam_nuevo > 0 && datos_nuevo == NULL) {
        return false;
    }
    vector->datos = datos_nuevo;
    vector->tam = tam_nuevo;
    return true;
}
