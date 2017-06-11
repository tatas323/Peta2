#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
 * Devuelve en un arreglo dinámico terminado en NULL con todos los subsegmentos
 * de ‘str’ separados por el carácter ‘sep’. Tanto el arreglo devuelto como las
 * cadenas que contiene son allocadas dinámicamente.
 *
 * Quien llama a la función toma responsabilidad de la memoria dinámica del
 * arreglo devuelto. La función devuelve NULL si falló alguna llamada a
 * malloc(), o si ‘sep’ es '\0'.
 */
char* mystrcat( char* str, char* strv ) {
    while (*str)
        str++;
    while (true)
        if(!(*str++ = *strv++)) break;
    return str=str-1;
}

char** split(const char* str, char sep) {
    size_t len = strlen(str);
    char **strv = malloc((len*sizeof(char *))+ 2*sizeof(char*));
    if(!strv)
        return  NULL;
    char buffer[len+1];
    size_t p_str =0, p_sv = 0;    //p_sv== posicion string vector  p_str == posicion de string
    while (p_str <= len) {
        size_t p_buf=0; //p_buff== posicion buffe
        while(str[p_str]!=sep && p_str!=len){
            buffer[p_buf]=str[p_str];
            p_str++;
            p_buf++;
            if(p_buf==len||p_str==len) break;
        }
        p_str++;
        buffer[p_buf]='\0';
        strv[p_sv] = malloc((sizeof(char)*strlen(buffer))+1);
        if(!strv[p_sv])
            return NULL;
        strcpy(strv[p_sv],buffer);
        p_sv++;
    }
    strv[p_sv]=NULL;
    return strv;
}


/*
 * Devuelve una cadena, allocada dinámicamente, resultado de unir todas las
 * cadenas del arreglo terminado en NULL ‘strv’.
 *
 * Quien llama a la función toma responsabilidad de la memoria dinámica de la
 * cadena devuelta. La función devuelve NULL si no se pudo allocar memoria.
 */
char* unir(char** strv, char sep){
    if(!strv){
        char* str= malloc(1);
        str[0]='\0';
        return str;
    }
    char separador[1];
    separador[0]=sep;
    separador[1]='\0';
    size_t len_str=0;
    size_t pos_strv=0;
    while(strv[pos_strv]) {
        size_t len_strv = strlen(strv[pos_strv])+1;
        len_str = len_str + len_strv;
        pos_strv++;
    }

    char* str= malloc(len_str* sizeof(char)+1);
    char* curr_ptr=str;
    if(!curr_ptr) return NULL;
    pos_strv=0;
    str[pos_strv]='\0';
    while(strv[pos_strv]) {
        curr_ptr= mystrcat(curr_ptr,strv[pos_strv]);
        pos_strv++;
        if(strv[pos_strv])
            curr_ptr=mystrcat(curr_ptr,separador);
    }
    return str;
}

/*
 * Libera un arreglo dinámico de cadenas, y todas las cadenas que contiene.
 */
void destruir_strv(char* strv[]){
    int i=0;
    while(strv[i]){
        free(strv[i]);
        i++;
    }
    free(strv);
}