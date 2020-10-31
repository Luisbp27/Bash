#include <stdio.h>

/*
Esta función calcula el nº de bytes de la cadena apuntada por str, sin incluir el carácter nulo de terminación ‘\0’ .
Devuelve la longitud de la cadena apuntada por str. No devuelve error.
*/
size_t my_strlen(const char *str) {
    size_t len = 0;

    for (len = 0; len < str[len]; len++)

    return len;
}

/*
Esta función compara las cadenas apuntadas por str1 y str2.
Devuelve un entero:
    < 0 indica que str1 < str2.
    > 0 indica que str2 < str1.
    = 0 indica que str1 = str2.
No se basa en la longitud sino en los códigos ASCII. Cuando encuentra uno 
diferente reporta el resultado calculado como la resta de los códigos ASCII 
de los caracteres diferentes.
*/
int my_strcmp(const char *str1, const char *str2) {
    int i = 0;
    int cmp = 0;

    while (str1[i] && (str1[i] != str2[i])) {
        if (str1[i] != str2[i]) {
            // Realizamos la diferencia correspondiente a los caracteres ASCII
            // como hace srtcmp()
            cmp = *(const unsigned char *)str1 - *(const unsigned char *)str2;
        }

        i++;
    }

    return cmp;
}

/*
La función strcpy() copia la cadena apuntada por src (con el carácter de terminación ‘\0’) 
en la memoria apuntada por dest.
Devuelve el puntero dest. No devuelve error.
*/
char *my_strcpy(char *dest, const char *src) {
    int c = 0;

    for (int i = 0; src[i]; i++,c++) {
        dest[c] = src[c];
    }

    return dest;
}

/*
La función strncpy() copia n caracteres de la cadena apuntada por src (con el carácter de terminación ‘\0’) 
en la memoria apuntada por dest. Devuelve el puntero dest. No devuelve error.
En caso de que strlen(src) < n, el resto de la cadena apuntada por dest ha de ser rellenado con 0s. 
*/
char *my_strncpy(char *dest, const char *src, size_t n) {
    char* paux = dest;
    int len = my_strlen(src);

    if (n <= len) { // Copiamos n caracteres sin '\0'
        while (n) {
            *paux = *src;
            paux++;
            src++;
            n--;
        }
    }else { // Copiamos todos los carácteres y rellenamos con '\0'
        int resto = n - (len + 1);

        while (len) {
            *paux = *src;
            paux++;
            src++;
            len--;
        }

        // Una vez copiados los carácteres añadimos '\0'
        *paux = '\0';
        while (resto) {
            paux++;
            resto--;
            *paux = '\0';
        }
    }

    return dest;
}

/*
La función strcat() añade la cadena apuntada por src (terminada con el carácter nulo) 
a la cadena apuntada por dest (también terminada con el carácter nulo).
El primer carácter de src sobreescribe el carácter nulo de dest. 
Devuelve el puntero dest. No devuelve error.
*/
char *my_strcat(char *dest, const char *src) {
        // Guardamos el puntero para añadir la concatenación
        char* new_dest = dest;
        
        // Nos movemos al final de dest
        while(*dest) {
          dest++;
        }

        // Concatenamos 'dest' con 'src'
        while(*src) {
          *dest++ = *src++;
        }
        
        //Añadimos el null a dest
        *dest = '\0'; 
    
    return new_dest;
}
