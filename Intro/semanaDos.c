#include <stdio.h>
#define PI 3.141593

int ejercicio1() {
    printf("\n*** Cálculo del cuadrado de un número entero ***");
    printf("\n Introduce el número:");

    int numero;
    scanf("%d", &numero);

    printf("El cuadrado de %d es %d \n", numero, numero*numero);
}

int ejercicio2() {
    printf("\n*** Cálculo del área de un círculo ***");
    printf("\n Introduce el radio: ");
    
    float radio;
    scanf("%f", &radio);
    printf("El área del círculo de radio %f es %f\n", radio, PI * radio * radio);
}

int ejercicio3() {
    printf("\n*** Conversión de grados Fahrenheit a grados Centígrados***");
    printf("\n Introduce grados en Fahrenheit:");

    float gradosFahrenheit;
    scanf("%f", &gradosFahrenheit);
    float gradosCentigrados = (5/9) * (gradosFahrenheit - 32);
    printf("\n%f grados Farenheit son %f grados Centígrados\n", gradosFahrenheit, gradosCentigrados);
}

int ejercicio4() {
    printf("\n*** Determinar si un número es par o impar ***");
    printf("\nIntroduce un número: ");

    int numero;
    scanf("%d", &numero);

    if(numero % 2 == 0) {
        printf("\nEl número %d es par\n", numero);
    }else {
        printf("\nEl número %d es impar\n", numero);
    }
}

int ejercicio5() {
    printf("\n*** Determinar la calificación cualitativa ***");
    printf("\nIntroduce la nota: ");

    float nota;
    scanf("%f", &nota);

    if(0 <= nota && nota < 5) {
        printf("\nInsuficiente\n");
    }else if(5 <= nota && nota < 7) {
        printf("\nSuficiente\n");
    }else if(7 <= nota && nota < 9) {
        printf("\nNotable\n");
    }else if(9 <= nota && nota <= 10) {
        printf("\nSobresaliente\n");
    }else {
        printf("\n* Calificación no cualitativa\n");
    }
}

int ejercicio6() {
    printf("\n*** Determinar si continuar o no ***");
    printf("\nDeseas continuar (S) o no (N) ?\n");

    char eleccion;
    scanf(" %c", &eleccion);

    switch(eleccion) {
        case 'S':
            printf("\nAhora seguimos\n");
            break;

        case 'N':
            printf("\nNos vemos en otra ocasión\n");
            break;

        default:
            printf("\nOpción incorrecta\n");
            break;
    }
}

int ejercicio7() {
    printf("\n*** Números múltiplos de 5 ***");
    printf("\n");

    int contador = 0;
    for (int i = 1; i <= 100; i++) {
        if(i % 5 == 0) {
        	printf("%d\t", i);
        	contador++;
        }
        if(contador % 5 == 0) {
        	printf("\n");
        }
    }
    
}

int ejercicio8() {
    printf("\n*** Cálculo de 1 + 2 + ... + N ***");
    printf("\nIntroduce un número N: ");

    int numero;
    scanf("%d", &numero);

    int suma = 0;
    while(numero != 0) {
        suma += numero;
        numero--;
    }

    printf("\nEl resultado es %d\n", suma);
}

int ejercicio9() {
    printf("\n*** Determinar si un número es par o impar ***");
    int numero;

    do {
        printf("\nIntroduce un número: ");
        scanf("%d", &numero);

        if(numero % 2 == 0) {
            printf("\nEl número %d es par\n", numero);
        }else {
            printf("\nEl número %d es impar\n", numero);
        }

    }while(numero != 0);
}

// Ejercicio 10

void max(int a, int b) {
    if(a < b) {
        printf("\nmax(%d, %d) = %d\n", a, b, b);
    }else {
        printf("\nmax(%d, %d) = %d\n", a, b, a);
    }
}

int ejercicio10(){
    printf("\n*** Función máximo de dos números enteros ***");
    printf("\nIntroduce dos números: ");

    int numero1, numero2;
    scanf("%d", &numero1);
    scanf("%d", &numero2);

    max(numero1, numero2);
}

// Ejercicio 11

int contarCaracteres(void) {
    int contador = 0;
    char caracter;
    caracter = getchar();

    while(caracter != EOF) {
        contador++;
        caracter = getchar();
    }

    return contador;
}

int ejercicio11() {
    printf("\n*** Función contar caracteres de stdin hasta EOF ***");

    int numCaracteres = contarCaracteres;
    printf("\nHas escrito %d caracteres\n", numCaracteres);
}

// Ejercicio 12

int factorial(int num) {
    if(num <= 1) {
        return 1;
    } 

    return num * factorial(num - 1);
}

int ejercicio12() {
    printf("\n*** Cálculo del factorial de un número ***");
    printf("\nIntroduce un número: ");

    int numero;
    scanf("%d", &numero);

    printf("\n%d! = %d\n", numero, factorial(numero));

}

// Programa Principal

int main() {
    system("clear");
    printf("\nEscoja el ejercicio que desea ejecutar: ");
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

        case 8:
            ejercicio8();
            break;

        case 9:
            ejercicio9();
            break;

        case 10:
            ejercicio10();
            break;

        case 11:
            ejercicio11();
        break;

        case 12:
            ejercicio12();
            break;

         default:
            printf("\n ***Introduce un número válido***");
    }


    return 0;
}