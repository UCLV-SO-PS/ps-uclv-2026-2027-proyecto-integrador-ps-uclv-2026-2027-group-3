#ifndef MONITOR_H
#define MONITOR_H

typedef struct {
    char codigo[7];
    char titulo[50];
    float puntuacion;
    int votos;
} Episodio;

void inicializar_bd();
int buscar_episodio(const char* codigo, Episodio* resultado);
void formatear_respueasta(const Episodio* ep, char* buffer);

#endif
