#include <stdio.h>
#include <string.h>

int ejercicio1() {
    printf("\n*** Eejrcicio 1 ***");

    int x, y;
    int *px;

    x = 5;
    px = &x;
    y = *px;

    printf("\nDirección de la variable x: %p", &x);
    printf("\nValor de x: %d", x);
    printf("\nDirección de px: %p", &px);
    printf("\nValor de px: %d", px);
    printf("\nDirección de y: %p", &y);
    printf("\nValor de *px: %d", *px);
    printf("\nValor de y: %d", y);
}

int visualizar(int newX, int newPX) {
    printf("\nValor de x: %d", newX);
    printf("\nDirección de x: %p", &newX);
    printf("\nValor de *px: %d", &newPX);
    printf("\nValor de px: %d", newPX);
}

int ejercicio2() {
    printf("\n*** Ejercicio 2 ***");

    int x, *px;

    // Apartado A
    printf("\nApartado A");
    x = 12;
    px = &x;

    visualizar(x, *px);

    // Apartado B
    printf("\nApartado B");
    *px = *px + 10;

    visualizar(x, *px);

    // Apartado C
    printf("\nApartado C");
    x = *px + 10;

    visualizar(x, *px);

    // Apartado D
    printf("\nApartado D");
    *px += 1;

    visualizar(x, *px);
}

int ejercicio3() {
    printf("\n*** Ejercicio 3 ***");
    
    void function(int a, int b);

    int x = 2;
    int y = 5;
    function(x, y);

    void functionPuntero(int *a, int *b);
    functionPuntero(&x, &y);


}

int ejercicio4() {
    printf("\n*** Ejercicio 4 ***");

    int my_array = {100, 101, 102, 103, 104, 105};
    int *ptr;
    ptr = my_array; // De esta forma ptr apunta al primer valor del array

    printf("\n\t* Primer bucle *");
    for (int i = 0; i < 5; i++) {
        printf("\nValor %d es: %d", i, my_array[i]);
    }

    printf("\n\t* Segundo bucle *");
    for (int i = 0; i < 5; i++) {
        printf("\nValor %d es: %d", *(ptr + i));
    }
}

int ejercicio5() {
    printf("\n*** Ejercicio 5 ***");

    char my_string[5] = "hola";
    char my_string1[] = {'h', 'o', 'l', 'a', '\0'};

    char src [10];
    char dest[10];
    strcpy(src, "Hola");
    strcpy(dest, src);

    char *p_my_string = "Hola";
    char *p_my_string2 = p_my_string;
}

int ejercicio6() {
    printf("\n*** Ejercicio 6 ***");
}

int ejercicio7() {
    printf("\n*** Ejercicio 7 ***");
}

int main() {
    printf("\nElige el ejercicio que deseas ejecutar: \n");
    
    int eleccion;
    scanf("%d", &eleccion);

    switch(eleccion) {
        case 1:
            ejercicio1();
            break;

        case 2:
            ejercicio2();
            break;

        case 3:
            ejercicio3();
            break;

        case 4:
            ejercicio4();
            break;

        case 5:
            ejercicio5();
            break;

        case 6:
            ejercicio6();
            break;

        case 7:
            ejercicio7();
            break;    
    }

    return 0;
}