// NIVEL 2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG 1
#define COMMAND_LINE_SIZE 1024
#define ARGS_SIZE 64
#define PROMPT '$'

#define RED "\x1b[91m"
#define GREEN "\x1b[92m"
#define YELLOW "\x1b[93m"
#define BLUE "\x1b[94m"
#define MAGENTA "\x1b[95m"
#define CYAN "\x1b[96m"
#define WHITE "\x1b[97m"
#define COLOR_RESET "\x1b[0m"

#define BLOND "\x1b[1m"

char line[COMMAND_LINE_SIZE];

// Funciones
char *read_line(char *line);
int execute_line(char *line);
int parse_args(char **args, char *line);
int check_internal(char **args);
int internal_cd(char **args);
int internal_export(char **args);
int internal_source(char **args);
int internal_jobs(char **args);

/*
* Main del programa.
*/
int main() {
    while (1)
        if (read_line(line)) {
            execute_line(line);
        }

    return 0;
}

/**
 * Método para remplazar una subcadena por otra subcadena en una cadena
 **/
char *replaceWord(const char *cadena, const char *cadenaAntigua, const char *nuevaCadena) {
    char *resultado;
    int i;
    int contador = 0;
    int newWorldLength = strlen(nuevaCadena);
    int oldWorldLength = strlen(cadenaAntigua);

    // Contando el número de veces palabra antigua que sale en el Sring
    for (i = 0; cadena[i] != '\0'; i++) {
        if (strstr(&cadena[i], cadenaAntigua) == &cadena[i]) {
            contador++;
            // Saltar al índice después de la palabra antigua.
            i += oldWorldLength - 1;
        }
    }

    // Reserva de espacio suficiente para la nueva cadena
    if ((resultado = malloc(i + contador * (newWorldLength - oldWorldLength) + 1))) {
        i = 0;

        while (*cadena) {
            // Comparar la subcadena con el resultado
            if (strstr(cadena, cadenaAntigua) == cadena) {
                strcpy(&resultado[i], nuevaCadena);
                i += newWorldLength;
                cadena += oldWorldLength;
            } else {
                resultado[i++] = *cadena++;
            }
        }

        resultado[i] = '\0';
    } else {
        perror("Error");
    }

    return resultado;
}

/*
* Método para imprimir el PROMPT
*/
void imprimir_prompt() {
    // Obtiene USERNAME
    char *user = getenv("USER");
    char *prompt;

    if ((prompt = malloc((sizeof(char) * COMMAND_LINE_SIZE) - sizeof(user)))) {
        // Obtiene el directorio de trabajo actual.
        getcwd(prompt, COMMAND_LINE_SIZE);

        if (strcmp(prompt, getenv("HOME"))) {
            if (strstr(prompt, getenv("HOME"))) {
                prompt = replaceWord(prompt, getenv("HOME"), "~");
            }
        }

        // Imprimimos el el PROMPT "personalizado"
        printf(BLOND RED "%s:" BLUE "%s " COLOR_RESET YELLOW "%c: " COLOR_RESET, user, prompt, PROMPT);
    } else  {
        perror("Error");
    }

    free(prompt);
    fflush(stdout);
}

/*
* Leer una linea de la consola
*/
char *read_line(char *line) {
    imprimir_prompt();

    // Lee la entrada introducida en stdin por el usuario
    if (fgets(line, COMMAND_LINE_SIZE, stdin) == NULL) {
        perror("Error");
    }

    return line;
}

/*
* 
*/
int execute_line(char *line) {
    // Reservamos memoria para los tokens
    char **args = malloc(sizeof(char *) * ARGS_SIZE);

    if (args == NULL) {
        fprintf(stderr, "Memoria dinamica llena.");
    }

    if (args) {
        // Parseamos
        parse_args(args, line);

        if (args[0]) {
            check_internal(args);
        }
    }

    // Liberamos memoria
    free(args);
}

// {line hacer esto #para esto} args[x][0]
int parse_args(char **args, char *line) {
    int nToken = 0;
    const char s[5] = " \t\r\n";
    char *token;

    token = strtok(line, s);
    args[nToken] = token;

    while (token != NULL) {
        #if DEBUG
            printf("[parse_args() → token %d: %s]\n", nToken, token);
        #endif

        // Descartamos comentarios
        if (*(token) != '#') {
            args[nToken] = token;
        } else {
            // Añadimos NULL
            token = NULL;
            args[nToken] = token;
            #if DEBUG
                printf("[parse_args() → token %d corregido: %s]\n", nToken, token);
            #endif
        }

        token = strtok(NULL, s);
        nToken++;
    }

    return nToken;
}

/*
* 
*/
int check_internal(char **args) {
    int comandoInterno = 0;

    const char cd[] = "cd";
    const char export[] = "export";
    const char source[] = "source";
    const char jobs[] = "jobs";
    const char fg[] = "fg";
    const char bg[] = "bg";
    const char exit[] = "exit";

    if (!strcmp(args[0], cd)) {
        internal_cd(args);
        comandoInterno = 1;
    } else if (!strcmp(args[0], export)) {
        internal_export(args);
        comandoInterno = 1;
    } else if (!strcmp(args[0], source)) {
        internal_source(args);
        comandoInterno = 1;
    } else if (!strcmp(args[0], jobs)) {
        internal_jobs(args);
        comandoInterno = 1;
    } else if (!strcmp(args[0], fg)) {
        internal_fg(args);
        comandoInterno = 1;
    } else if (!strcmp(args[0], bg)) {
        internal_bg(args);
        comandoInterno = 1;
    } else if (!strcmp(args[0], exit)) {
        internal_exit(args);
        comandoInterno = 1;
    }

    return comandoInterno;
}

/*
* Método que borra un caracter de un "array/puntero"
*/
void borradorCaracter(char *args, char caracter) {
    int indice = 0;
    int indiceNuevo = 0;

    while (args[indice]) {
        if (args[indice] != caracter) {
            args[indiceNuevo] = args[indice];
            indiceNuevo++;
        }

        indice++;
    }

    args[indiceNuevo] = 0;
}

/*
* Utiliza la llamada al sistema chdir() para cambiar de directorio
*/
int internal_cd(char **args) {
    // Falta control de error
    char *linea = malloc(sizeof(char) * COMMAND_LINE_SIZE);

    if (linea == NULL) {
        fprintf(stderr, "No hay memoria dinámica disponible en este momento.");
    }

    // Concatenamos los args
    for (int i = 0; args[i]; i++) {
        strcat(linea, " ");
        strcat(linea, args[i]);
    }

    // Separadores en ASCII: barra,comillas,comilla, espacio
    const int sep[] = {92, 34, 39, 32};

    if (args[2] != NULL) {
        // Miramos si es un caso escepcional
        int numeroLetrasArgs1 = strlen(args[1]);
        int permitido = 1;
        // Miramos comilla o comillas

        char *ruta;
        // Comilla
        if (args[1][0] == (char)sep[1]) {
            ruta = strchr(linea, (char)(sep[1]));
            borradorCaracter(ruta, (char)sep[1]);
        }

        // Comillas
        else if (args[1][0] == (char)sep[2]) {
            ruta = strchr(linea, (char)(sep[2]));
            borradorCaracter(ruta, (char)sep[2]);
        }

        // Barra
        else if (args[1][numeroLetrasArgs1 - 1] == (char)sep[0]) {
            ruta = strchr(linea, args[1][0]);
            borradorCaracter(ruta, (char)sep[0]);
        } else {
            permitido = 0;
        }

        // Si se permiten 2 palabras después del cd
        if (!permitido) {
            fprintf(stderr, "Error: Too much arguments\n");
        } else {
            if (chdir(ruta)) {
                perror("Error");
            }
        }
    }

    // Si es una palabra
    else {
        if (args[1] == NULL) {
            if (chdir(getenv("HOME"))) {
                perror("Error");
            }
        } else {
            if (chdir(args[1])) {
                perror("Error");
            }
        }
    }

    #if DEBUG
        char *prompt;
        if ((prompt = malloc((sizeof(char) * COMMAND_LINE_SIZE)))) {
        // Gets the current work directory.
        getcwd(prompt, COMMAND_LINE_SIZE);

        printf("[internal_cd() → %s]\n", prompt);
        } else{
        perror("Error");
        }

        ree(prompt);
    #endif

    free(linea);

    return 1;
}

/*
*
*/
int internal_export(char **args) {
    const char *separador = "=";
    char *nombre, *valor;

    if (args[1]) {
        nombre = strtok(args[1], separador);
        valor = strtok(NULL, separador);
    }

    if (nombre == NULL || valor == NULL) {
        fprintf(stderr, "Error de sintaxis");
    } else {
        #if DEBUG
            printf("[internal_export() → nombre: %s]\n", nombre);
            printf("[internal_export() → valor: %s]\n", valor);
            printf("[internal_export() → antiguo valor para %s: %s]\n", nombre, getenv(nombre));
        #endif
        setenv(nombre, valor, 1);
        #if DEBUG
            printf("[internal_export() → nuevo valor para %s: %s]\n", nombre, getenv(nombre));
        #endif
    }

    return 1;
}

int internal_source(char **args) {
    #if DEBUG
        printf("[internal_source() → Esta función ejecutará un fichero de líneas de comandos]\n");
    #endif

    return 1;
}

int internal_jobs(char **args) {
    #if DEBUG
        printf("[internal_jobs() → Esta función mostrará el PID de los procesos que no estén en foreground]\n");
    #endif
    
    return 1;
}

int internal_fg(char **args) {
    #if DEBUG
        printf("[internal_fg() → Esta función parsará/activará a primer plano procesos]\n");
    #endif
    
    return 1;
}

int internal_bg(char **args) {
    #if DEBUG
        printf("[internal_bg() → Esta función parsará/activará a segundo plano procesos]\n");
    #endif
    
    return 1;
}

int internal_exit(char **args) {
    #if DEBUG
        printf("[internal_exit() → Esta función sale del mini shell]\n");
    #endif
    
    exit(0);
    
    return 1;
}