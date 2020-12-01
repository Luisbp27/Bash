// NIVEL 3

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait>

#define DEBUG0 0
#define DEBUG1 0
#define DEBUG2 0
#define DEBUG3 1

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
int internal_fg(char **args);
int internal_bg(char **args);
int internal_exit(char **args);
int internal_fg(char **args);

int chdir();
int getcwd();
int setenv();
int fork();
int execvp();
int getppid();
int getpid();

/*
* Main del programa.
*/
int main() {
    while (1)
        if (read_line(line)) execute_line(line);

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
*   Método para imprimir el PROMPT
*/
void imprimir_prompt() {
    // Coge el nombre de usuario
    char *user = getenv("USER");

    char *prompt = malloc(sizeof(char) * COMMAND_LINE_SIZE);

    // Gets the current work directory.
    getcwd(prompt, COMMAND_LINE_SIZE);
    // Prints the prompt and the separator.
    printf(BLOND RED "%s:" BLUE "%s " COLOR_RESET YELLOW "%c: " COLOR_RESET, user, prompt, PROMPT);

    // frees the memory for prompt.
    free(prompt);

    fflush(stdout);
}

/*
Leer una linea de la consola
*/
char *read_line(char *line) {
    imprimir_prompt();
    char* ptr = fgets(line, COMMAND_LINE_SIZE, stdin);
   
    // Leemos la entrada introducida en stdin por el usuario
    if (ptr == NULL) {
        printf("\r\n");

        if (feof(stdin)) {
            printf("Adeu\n");
            exit(0);
        } else {
            perror("Error");
        }
    }

    return line;
}

/*
*
*/
int execute_line(char *line) {
    //Reservamos memoria para los tokens
    char **args = malloc(sizeof(char *) * ARGS_SIZE);

    if (args != NULL) {
        // Parseamos
        parse_args(args, line);

        if (args[0]) {
            if (!check_internal(args)) {
                int state;
                pid_t pid = fork();

                // Hijo
                if (pid == 0) {
                    #if DEBUG3
                        printf("[execute_line() → PID padre: %d]\n", getppid());
                        printf("[execute_line() → PID hijo: %d]\n", getpid());
                    #endif
                    
                    if (execvp(args[0], args)) {
                        fprintf(stderr, "Error al leer el comando externo: %s.\n",args[0]);
                        //Terminación anormal
                        exit(EXIT_FAILURE);
                    }

                    // Salimos sin errores (Terminación Normal)
                    exit(EXIT_SUCCESS);

                // Padre    
                } else if (pid > 0) {
                    pid  = wait(&state);

                    // Hijo ha terminado de manera normal
                    if (WIFEXITED(state)) {
                        #if DEBUG3
                            printf("[EL proceso hijo %d ha finalizado con exit(), estado: %d]\n",pid ,WEXITSTATUS(state));
                        #endif
                    }

                    // Hijo ha finalizado por señal
                    if (WIFSIGNALED(state)) {
                        #if DEBUG3
                            printf("[EL proceso hijo %d ha finalizado por final, estado: %d]\n",pid ,WTERMSIG(state));
                        #endif
                    }

                // Error de fork()
                } else {
                    perror("Error fork");
                    //Terminación anormal
                    exit(EXIT_FAILURE);
                }
            }
        }
    } else {
        fprintf(stderr, "Memoria dinámica llena.\n");
    }

    // Liberamos memoria
    free(args);
}

/**
 * 
 */
int parse_args(char **args, char *line) {
    int nToken = 0;
    const char s[5] = " \t\r\n";
    char *token;

    token = strtok(line, s);
    args[nToken] = token;

    while (token != NULL)
    {

    #if DEBUG
        printf("[parse_args() → token %d: %s]\n", nToken, token);
    #endif
        //Descartamos comentarios
        if (*(token) != '#')
        {
            args[nToken] = token;
        }
        else
        {
            //Añadimos NULL
            token = NULL;
            args[nToken] = token;
    #if DEBUG
            printf("[parse_args() → token %d corregido: %s]\n", nToken, token);
    #endif
        }

        //Siguiete
        token = strtok(NULL, s);
        nToken++;
    }

    return nToken;
}

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
Utiliza la llamada al sistema chdir() para cambiar de directorio
*/
int internal_cd(char **args) {
    // Falta control de error
    char *linea = malloc(sizeof(char) * COMMAND_LINE_SIZE);
    // Separadores: comilla,comillas, barra
    const int sep[] = {34, 39, 92};

    if (args[2]) {
        fprintf(stderr, "Error: Too much arguments\n");
    } else {
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

    free(linea);

    return 1;
}

int internal_export(char **args) {
    const char *separador= "=";
    char *nombre, *valor;

    if (args[1]) {
        nombre = strtok(args[1], separador);
        valor = strtok(NULL, separador);
    }

    if (nombre == NULL || valor == NULL){
        fprintf(stderr, "Error de sintaxis");
    } else { 
        printf("[internal_export() → nombre: %s]\n", nombre);
        printf("[internal_export() → valor: %s]\n", valor);
        printf("[internal_export() → antiguo valor para %s: %s]\n", nombre, getenv(nombre));
        setenv(nombre, valor, 1);
        printf("[internal_export() → nuevo valor para %s: %s]\n", nombre, getenv(nombre));
    }

    return 1;
}

int internal_source(char **args) {
    // Creamos la variable y reservamos memoria para leer las lineas del fichero
    char *linea = (char *)malloc(sizeof(char) * COMMAND_LINE_SIZE);

    if (linea) {
        // Declaramos, instanciamos y creamos el enlace al fichero a leer
        FILE *fichero = fopen(args[1], "r");

        // Si existe el fichero
        if(fichero) {
            // Leemos las lineas y las ejecutamos
            while (fgets(linea, COMMAND_LINE_SIZE, fichero)) {
                execute_line(linea);
                fflush(fichero);
            }

            fclose(fichero);
            free(linea);

            return EXIT_SUCCESS;
        } else {
            // Error al leer el fichero
            perror("Error");
            free(linea);
        }
    }

    return EXIT_FAILURE;

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