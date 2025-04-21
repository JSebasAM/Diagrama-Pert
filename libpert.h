#ifndef LIBPERT_H
#define LIBPERT_H

typedef struct Nodo {
    int destino;
    struct Nodo *sig;
} Nodo;

typedef struct {
    char nombre[50];
    int duracion;
    int ES, EF, LS, LF, holgura;
    Nodo *sucesores;
    int num_precedentes;
} Actividad;

void agregarArista(Actividad *actividades, int origen, int destino);

int buscarIndice(Actividad *actividades, int num, const char *nombre);

void calcularTempranos(Actividad *actividades, int num);

void calcularTardios(Actividad *actividades, int num);

void mostrarResultados(Actividad *actividades, int num);


#endif
