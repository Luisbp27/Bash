#include <stdio.h>

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

    visualizar(x, px);

    // Apartado B
    printf("\nApartado B");
    *px = *px + 10;

    visualizar(x, px);

    // Apartado C
    printf("\nApartado C");
    x = *px + 10;

    visualizar(x, px);

    // Apartado D
    printf("\nApartado D");
    *px += 1;

    visualizar(x, px);
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
}

int ejercicio5() {
    printf("\n*** Ejercicio 5 ***");
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
            break;

        case 5:
            break;

        case 6:
            break;

        case 7:
            break;    
    }

    return 0;
}