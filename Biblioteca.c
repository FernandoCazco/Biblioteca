
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIBROS    10
#define MAX_TITULO   101
#define MAX_AUTOR     51
#define MAX_ESTADO    11

typedef struct {
    int  id;
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    int  anio;
    char estado[MAX_ESTADO];
} Libro;

Libro biblioteca[MAX_LIBROS];
int   totalLibros = 0;

void limpiarBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void imprimirLinea(void) {
    printf("------------------------------------------------------------------\n");
}

int idExiste(int id) {
    for (int i = 0; i < totalLibros; i++) {
        if (biblioteca[i].id == id) return 1;
    }
    return 0;
}

int buscarIndicePorID(int id) {
    for (int i = 0; i < totalLibros; i++) {
        if (biblioteca[i].id == id) return i;
    }
    return -1;
}

/* Lee un entero validado */
int leerEntero(const char *mensaje) {
    int valor;
    char basura;
    while (1) {
        printf("%s", mensaje);
        if (scanf("%d%c", &valor, &basura) == 2 && basura == '\n') {
            return valor;
        }
        limpiarBuffer();
        printf("  [!] Entrada invalida. Ingrese solo numeros enteros.\n");
    }
}

void leerCadena(const char *mensaje, char *destino, int maxLen) {
    while (1) {
        printf("%s", mensaje);
        if (fgets(destino, maxLen, stdin)) {
            int len = strlen(destino);
            if (len > 0 && destino[len - 1] == '\n')
                destino[len - 1] = '\0';
            if (strlen(destino) == 0) {
                printf("  [!] El campo no puede estar vacio.\n");
                continue;
            }
            return;
        }
        limpiarBuffer();
        printf("  [!] Error de lectura. Intente de nuevo.\n");
    }
}

