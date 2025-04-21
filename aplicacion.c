#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpert.h>

int main() {
    int num;
    printf("Cantidad de actividades: ");
    scanf("%d", &num);
    getchar(); // limpiar buffer

    Actividad *actividades = malloc(sizeof(Actividad) * num);
    if (!actividades) {
        printf("Error al asignar memoria\n");
        return 1;
    }

    for (int i = 0; i <num; i++) {
        printf("\nNombre de la actividad %d: ", i + 1);
        fgets(actividades[i].nombre, sizeof(actividades[i].nombre), stdin);
        actividades[i].nombre[strcspn(actividades[i].nombre, "\n")] = 0;

        actividades[i].sucesores = NULL;
        actividades[i].num_precedentes = 0;

        printf("Nombre del precedente(s) (0 si no tiene, separados por ', '): ");
        char linea_precedentes[200];
        fgets(linea_precedentes, sizeof(linea_precedentes), stdin);
        linea_precedentes[strcspn(linea_precedentes, "\n")] = 0;

        if (strcmp(linea_precedentes, "0") != 0) {
            char *token = strtok(linea_precedentes, ",");
            while (token != NULL) {
                while (*token == ' ') token++;  // Eliminar espacios al inicio

                int idx = buscarIndice(actividades, i, token); // buscar hasta i (actividades ya definidas)
                if (idx == -1) {
                    printf("Precedente \"%s\" no encontrado. Intenta de nuevo.\n", token);
                    i--; // Repetir esta actividad
                    break;
                } else {
                    agregarArista(actividades, idx, i); // idx → i
                    actividades[i].num_precedentes++;
                }

                token = strtok(NULL, ",");
            }
        }
        printf("Duración (unidades de tiempo): ");
        scanf("%d", &actividades[i].duracion);
        getchar();
    }
    calcularTempranos(actividades, num);
    calcularTardios(actividades, num);
    mostrarResultados(actividades, num);

    free(actividades);
    exit(EXIT_SUCCESS);

}
