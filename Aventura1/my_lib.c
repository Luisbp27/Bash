#include <stdio.h>

// Función que calcula el nº de bytes de la cadena apuntada por str y devuelve un entero
size_t my_strlen(const char *str) {
    size_t len = 0;

    for (len = 0; len < str[len]; len++)
    
    return len;
}

// Compara las cadenas apuntadas por str1 y str2 y devuelve un entero
int my_strcmp(const char *str1, const char *str2) {
    int i = 0;
    int cmp = 0;

    while(str[i] && (str[i] != str2[i])) {
        if(str1[i] != str2[i]) {
            cmp = str[i] - str2[i];
        }
        i++;
    }
    
    return cmp;
}

// Copia la cadena apuntada por src en la memoria apuntada por dest
char *my_strcpy(char *dest, const char *src) {
    int c = 0;
    char *org = dest;

    for (c; src[c]; c++) {
        dest[c] = src[c];
    }
    dest[c] = '\0';

    return org;    
}

//
char *my_strncpy(char *dest, const char *src, size_t n) {
}

char *my_strcat(char *dest, const char *src) {
    
}