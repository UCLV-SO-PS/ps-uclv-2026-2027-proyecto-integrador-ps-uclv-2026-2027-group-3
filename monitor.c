#include <stdio.h>
#include <string.h>
#include "monitor.h"

Episodio bd[6];

void inicializar_bd(){
    strcpy(bd[0].codigo, "S01E01"); strcpy(bd[0].titulo, "The Hedge Knight"); bd[0].puntuacion = 9.2; bd[0].votos = 45120;
    strcpy(bd[1].codigo, "S01E02"); strcpy(bd[1].titulo, "Hard Salt Beef"); bd[1].puntuacion = 8.8; bd[1].votos = 38900;
    strcpy(bd[2].codigo, "S01E03"); strcpy(bd[2].titulo, "The Squire"); bd[2].puntuacion = 9.5; bd[2].votos = 52400;
    strcpy(bd[3].codigo, "S01E04"); strcpy(bd[3].titulo, "Seven"); bd[3].puntuacion = 9.3; bd[3].votos = 41200;
    strcpy(bd[4].codigo, "S01E05"); strcpy(bd[4].titulo, "In the Name of my Mother"); bd[4].puntuacion = 9.7; bd[4].votos = 68300;
    strcpy(bd[5].codigo, "S01E06"); strcpy(bd[5].titulo, "The Morrow"); bd[5].puntuacion = 9.4; bd[5].votos = 49800;
}

int buscar_episodio(const char* codigo, Episodio* resultado){
    for(int i=0; i<6; i++){
        if(strcmp(bd[i].codigo, codigo) == 0){
            *resultado = bd[i];
            return 1;
        }
    }
    return 0;
}

void formatear_respuesta(const Episodio* ep, char* buffer){
    sprintf(buffer, "Episodio %s | Titulo %s | Puntuacion %.1f | Votos %d\n", ep->codigo, ep->titulo, ep->puntuacion, ep->votos);
}
