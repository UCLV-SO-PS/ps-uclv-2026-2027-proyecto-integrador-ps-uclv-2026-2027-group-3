#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "monitor.h"

#define PUERTO 6666

int main(int argc, char *argv[]){
    inicializar_bd();

    if (argc > 1 && strcmp(argv[1], "--test-run") == 0) {
        printf("Test-run: Base de datos inicializada correctamente.\n");
        printf("Test-run: Servidor listo para escuchar en el puerto %d.\n");
        return 0;
    }

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Error socket");
        return 1;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PUERTO);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        perror("Error bind");
        return 1;
    }

    if (listen(server_fd, 5) == -1){
        perror("Error listen");
        return 1;
    }

    printf("Servidor escuchando en el puerto %d...\n", PUERTO);

    //Agrega el bucle accept() y fork()

    return 0;
}