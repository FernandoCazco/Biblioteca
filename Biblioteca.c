
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

