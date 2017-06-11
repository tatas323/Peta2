#include "hash.h"
#include "tweet.h"
#include "strutil.h"
#include "bloom.h"
#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct campo{
    char* clave;
    size_t * apariciones;
}typedef campo_t;



/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/



int cmp (const void* a, const void *b){
    if(*(((campo_t*)a)->apariciones) == *(((campo_t*)b)->apariciones))
        return 0;
    if(*(((campo_t*)a)->apariciones) > *(((campo_t*)b)->apariciones))
        return 1;
    else
        return -1;
}


campo_t* crear_campo_tweet(const char * clave, size_t *  dato){
    campo_t* campo = malloc(sizeof(campo_t));
    if(!campo)
        return NULL;
    campo -> clave = malloc(sizeof(const char)* strlen(clave)+1);//Crear copia de clave
    strcpy(campo->clave,clave);
    campo-> apariciones = dato;
    return campo;
}


char** top_k(filter_t* filter, hash_t* hash,size_t k){
    hash_iter_t* iter=hash_iter_crear(hash);
    heap_t* heap=heap_crear(cmp);
    size_t valor[hash_cantidad(hash)];
    int i=0;
    while(!hash_iter_al_final(iter)){
        char *clave = (char *) hash_iter_ver_actual(iter);
        valor[i]=filter_report(filter, clave);
        campo_t* campo = crear_campo_tweet(clave, &valor[i]);
        if(i<k){
            heap_encolar(heap,campo);
        }
        else if(cmp(campo,heap_ver_max(heap))>0){
            campo_t* aux=heap_desencolar(heap);
            heap_encolar(heap,campo);
            free(aux->clave);
            free(aux);
        }
        else{
            free(campo->clave);
            free(campo);
        }
        hash_iter_avanzar(iter);
        i++;
    }
    char** hashtags=malloc(k*sizeof(char*));
    for (size_t j = 0; j<k ; j++) {
        campo_t* max=heap_desencolar(heap);
        hashtags[j]=malloc(sizeof(char)*strlen(max->clave)+1);
        hashtags[j]=max->clave;
        free(max);
    }
    heap_destruir(heap,free);
    hash_iter_destruir(iter);
    hash_destruir(hash);
    return hashtags;

}

char** line_split(FILE* arch,char* line){
    fscanf(arch,"%s ",line);
    return split(line,',');
}

int procesar_tweets(FILE* arch,size_t n, size_t k){
    filter_t* filter=filter_crear(n);
    char* hashtag=malloc(150*sizeof(char));
    while(!feof(arch)){
        hash_t* hash=hash_crear(NULL);
        for (int j = 0; j <n ; ++j) {
            int i=0;
            char** hashtags=line_split(arch,hashtag);
            while(hashtags[i]) {
                if(i!=0) {
                    hash_guardar(hash, hashtags[i], NULL);
                    filter_count(filter, hashtags[i]);
                }
                i++;
            }
            destruir_strv(hashtags);
            if(feof(arch)) break;
        }
        char** trending_tags = top_k(filter,hash,k);
        for(int c=0; c<k && trending_tags[c] ;c++) {
            fprintf(stderr, "%s\n", trending_tags[c]);
        }
        destruir_strv(trending_tags);
    }
    filter_destruir(filter);
    free(hashtag);
    fclose(arch);
    return 0;
}





int procesar_usuarios(FILE* arch, size_t n,size_t k){
    return 0;

}






int main(int argc , char* argv[]){
    if(argc!=3 && argc!=4){
        fprintf(stderr, "//%s//Numero incorrecto de argumentos\n",argv[0]);
        printf("%d",argc);
        return 1;
    }
    FILE* arch=freopen("tweets.txt","r",stdin);
    if(!arch){
        fprintf(stderr, "//%s//Archivo no presente\n",argv[0]);
        return 1;
    }

    printf("%d",argc);
    return procesar_tweets(arch,(size_t) atoi(argv[2]), (size_t) atoi(argv[3]));
}