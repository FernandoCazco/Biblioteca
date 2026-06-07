
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

void registrarLibro(void) {
    printf("\n=== REGISTRAR NUEVO LIBRO ===\n");

    if (totalLibros >= MAX_LIBROS) {
        printf("  [!] La biblioteca esta llena (maximo %d libros).\n", MAX_LIBROS);
        return;
    }

    Libro nuevo;

    while (1) {
        nuevo.id = leerEntero("  ID del libro     : ");
        if (nuevo.id <= 0) {
            printf("  [!] El ID debe ser un numero positivo.\n");
        } else if (idExiste(nuevo.id)) {
            printf("  [!] Ya existe un libro con ese ID. Use otro.\n");
        } else {
            break;
        }
    }

    leerCadena("  Titulo           : ", nuevo.titulo, MAX_TITULO);
    leerCadena("  Autor            : ", nuevo.autor,  MAX_AUTOR);

    while (1) {
        nuevo.anio = leerEntero("  Anio publicacion : ");
        if (nuevo.anio < 1000 || nuevo.anio > 2025) {
            printf("  [!] Ingrese un anio valido (1000 - 2025).\n");
        } else {
            break;
        }
    }

    strcpy(nuevo.estado, "Disponible");
    biblioteca[totalLibros++] = nuevo;
    printf("  [OK] Libro registrado exitosamente.\n");
}

/* Mostrar todos los libros en formato tabla */
void mostrarLibros(void) {
    printf("\n=== LISTA DE LIBROS ===\n");

    if (totalLibros == 0) {
        printf("  No hay libros registrados.\n");
        return;
    }

    imprimirLinea();
    printf("| %-4s | %-30s | %-20s | %-4s | %-10s |\n",
           "ID", "TITULO", "AUTOR", "ANIO", "ESTADO");
    imprimirLinea();

    for (int i = 0; i < totalLibros; i++) {
        printf("| %-4d | %-30s | %-20s | %-4d | %-10s |\n",
               biblioteca[i].id,
               biblioteca[i].titulo,
               biblioteca[i].autor,
               biblioteca[i].anio,
               biblioteca[i].estado);
    }
    imprimirLinea();
    printf("  Total de libros registrados: %d / %d\n", totalLibros, MAX_LIBROS);
}

void buscarLibro(void) {
    printf("\n=== BUSCAR LIBRO ===\n");

    if (totalLibros == 0) {
        printf("  No hay libros registrados.\n");
        return;
    }

    printf("  Buscar por:\n");
    printf("    1. ID\n");
    printf("    2. Titulo\n");
    int op = leerEntero("  Opcion: ");

    if (op == 1) {
        int id = leerEntero("  ID a buscar: ");
        int idx = buscarIndicePorID(id);
        if (idx == -1) {
            printf("  [!] No se encontro un libro con ID %d.\n", id);
        } else {
            imprimirLinea();
            printf("  ID              : %d\n",  biblioteca[idx].id);
            printf("  Titulo          : %s\n",  biblioteca[idx].titulo);
            printf("  Autor           : %s\n",  biblioteca[idx].autor);
            printf("  Anio publicacion: %d\n",  biblioteca[idx].anio);
            printf("  Estado          : %s\n",  biblioteca[idx].estado);
            imprimirLinea();
        }

    } else if (op == 2) {
        char termino[MAX_TITULO];
        leerCadena("  Titulo (o parte del titulo): ", termino, MAX_TITULO);

        int encontrados = 0;
        for (int i = 0; i < totalLibros; i++) {
            char tituloCopia[MAX_TITULO], terminoCopia[MAX_TITULO];
            strcpy(tituloCopia, biblioteca[i].titulo);
            strcpy(terminoCopia, termino);

            for (int j = 0; tituloCopia[j]; j++)
                if (tituloCopia[j] >= 'A' && tituloCopia[j] <= 'Z')
                    tituloCopia[j] += 32;
            for (int j = 0; terminoCopia[j]; j++)
                if (terminoCopia[j] >= 'A' && terminoCopia[j] <= 'Z')
                    terminoCopia[j] += 32;

            if (strstr(tituloCopia, terminoCopia)) {
                imprimirLinea();
                printf("  ID              : %d\n",  biblioteca[i].id);
                printf("  Titulo          : %s\n",  biblioteca[i].titulo);
                printf("  Autor           : %s\n",  biblioteca[i].autor);
                printf("  Anio publicacion: %d\n",  biblioteca[i].anio);
                printf("  Estado          : %s\n",  biblioteca[i].estado);
                imprimirLinea();
                encontrados++;
            }
        }
        if (encontrados == 0)
            printf("  [!] No se encontro ningun libro con ese titulo.\n");
        else
            printf("  Se encontraron %d resultado(s).\n", encontrados);

    } else {
        printf("  [!] Opcion no valida.\n");
    }
}

void actualizarEstado(void) {
    printf("\n=== ACTUALIZAR ESTADO DE LIBRO ===\n");

    if (totalLibros == 0) {
        printf("  No hay libros registrados.\n");
        return;
    }

    int id = leerEntero("  ID del libro a actualizar: ");
    int idx = buscarIndicePorID(id);

    if (idx == -1) {
        printf("  [!] No se encontro un libro con ID %d.\n", id);
        return;
    }

    printf("  Estado actual: %s\n", biblioteca[idx].estado);

    if (strcmp(biblioteca[idx].estado, "Disponible") == 0) {
        strcpy(biblioteca[idx].estado, "Prestado");
    } else {
        strcpy(biblioteca[idx].estado, "Disponible");
    }

    printf("  [OK] Estado actualizado a: %s\n", biblioteca[idx].estado);
}

void eliminarLibro(void) {
    printf("\n=== ELIMINAR LIBRO ===\n");

    if (totalLibros == 0) {
        printf("  No hay libros registrados.\n");
        return;
    }

    int id = leerEntero("  ID del libro a eliminar: ");
    int idx = buscarIndicePorID(id);

    if (idx == -1) {
        printf("  [!] No se encontro un libro con ID %d.\n", id);
        return;
    }

    printf("  Libro a eliminar: \"%s\" (ID %d)\n",
           biblioteca[idx].titulo, biblioteca[idx].id);
    printf("  Confirmar eliminacion (s/n): ");
    char conf[5];
    fgets(conf, sizeof(conf), stdin);

    if (conf[0] != 's' && conf[0] != 'S') {
        printf("  Operacion cancelada.\n");
        return;
    }

    for (int i = idx; i < totalLibros - 1; i++) {
        biblioteca[i] = biblioteca[i + 1];
    }
    totalLibros--;
    printf("  [OK] Libro eliminado exitosamente.\n");
}

void mostrarMenu(void) {
    printf("\n");
    imprimirLinea();
    printf("    SISTEMA DE GESTION DE BIBLIOTECA\n");
    imprimirLinea();
    printf("    1. Registrar libro\n");
    printf("    2. Mostrar todos los libros\n");
    printf("    3. Buscar libro\n");
    printf("    4. Actualizar estado de libro\n");
    printf("    5. Eliminar libro\n");
    printf("    6. Salir\n");
    imprimirLinea();
}

int main(void) {
    int opcion;

    printf("  Bienvenido al sistema de gestion de la biblioteca.\n");

    do {
        mostrarMenu();
        opcion = leerEntero("  Seleccione una opcion: ");

        switch (opcion) {
            case 1: registrarLibro();   break;
            case 2: mostrarLibros();    break;
            case 3: buscarLibro();      break;
            case 4: actualizarEstado(); break;
            case 5: eliminarLibro();    break;
            case 6: printf("\n  Hasta luego!\n\n"); break;
            default:
                printf("  [!] Opcion no valida. Elija entre 1 y 6.\n");
        }

    } while (opcion != 6);

    return 0;
}