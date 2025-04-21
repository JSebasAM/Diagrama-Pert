#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libpert.h"

void agregarArista(Actividad * actividades, int origen, int destino) {
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    nuevo->destino = destino;
    nuevo->sig = actividades[origen].sucesores;
    actividades[origen].sucesores = nuevo;
    actividades[destino].num_precedentes++;
}

int buscarIndice(Actividad * actividades,int num, const char *nombre) {
    for (int i = 0; i < num; i++) {
        if (strcmp(actividades[i].nombre, nombre) == 0)
            return i;
    }
    return -1;
}

void calcularTempranos(Actividad * actividades, int num) {
    int cambiando = 1;
    while (cambiando) {
        cambiando = 0;
        for (int i = 0; i < num; i++) {
            if (actividades[i].num_precedentes == 0 && actividades[i].EF == 0) {
                actividades[i].EF = actividades[i].duracion;
                cambiando = 1;
            }

            Nodo *nodo = actividades[i].sucesores;
            while (nodo) {
                int s = nodo->destino;
                if (actividades[s].ES < actividades[i].EF) {
                    actividades[s].ES = actividades[i].EF;
                    actividades[s].EF = actividades[s].ES + actividades[s].duracion;
                    cambiando = 1;
                }
                nodo = nodo->sig;
            }
        }
    }
}

void calcularTardios(Actividad * actividades, int num) {
    int duracion_total = 0;
    for (int i = 0; i < num; i++)
        if (actividades[i].EF > duracion_total)
            duracion_total = actividades[i].EF;

    for (int i = 0; i < num; i++) {
        actividades[i].LF = duracion_total;
        actividades[i].LS = actividades[i].LF - actividades[i].duracion;
    }

    int cambiando = 1;
    while (cambiando) {
        cambiando = 0;
        for (int i = num - 1; i >= 0; i--) {
            Nodo *nodo = actividades[i].sucesores;
            while (nodo) {
                int s = nodo->destino;
                if (actividades[i].LF > actividades[s].LS) {
                    actividades[i].LF = actividades[s].LS;
                    actividades[i].LS = actividades[i].LF - actividades[i].duracion;
                    cambiando = 1;
                }
                nodo = nodo->sig;
            }
            actividades[i].holgura = actividades[i].LS - actividades[i].ES;
        }
    }
}

void mostrarResultados(Actividad * actividades, int num) {
    printf("\n===== Resultados del Diagrama PERT =====\n");
    int duracion_total = 0;

    for (int i = 0; i < num; i++) {
        printf("Actividad %s - TE: %.2f, ES: %.2f, EF: %.2f, LS: %.2f, LF: %.2f, Holgura: %.2f",
               actividades[i].nombre,
               (float)actividades[i].duracion,
               (float)actividades[i].ES,
               (float)actividades[i].EF,
               (float)actividades[i].LS,
               (float)actividades[i].LF,
               (float)actividades[i].holgura);
        if (actividades[i].holgura == 0)
            printf(" <-- Camino Crítico");
        printf("\n");

        if (actividades[i].EF > duracion_total)
            duracion_total = actividades[i].EF;
    }

    printf("Duración total del proyecto: %.2f unidades de tiempo\n", (float)duracion_total);
}
