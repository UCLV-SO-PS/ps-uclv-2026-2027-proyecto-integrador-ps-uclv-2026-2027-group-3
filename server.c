#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "monitor.h"
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>

#define PUERTO 6666

//Manejador para cosechar hijos muertos y evitar zombies
void manejador_sigchld(int sig){
    while(waitpid(-1, NULL , WNOHANG)>0);
}

int main(int argc, char *argv[]){
    inicializar_bd();

    if (argc > 1 && strcmp(argv[1], "--test-run") == 0) {
        printf("Test-run: Base de datos inicializada correctamente.\n");
        printf("Test-run: Servidor listo para escuchar en el puerto %d.\n", PUERTO);
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

    // Configuro señal SIGCHLG para evitar un zombies
    struct sigaction sa;
    sa.sa_handler = manejador_sigchld;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; // Para que accept() no falle al recibir la señal
    sigaction(SIGCHLD , &sa, NULL);
    
    signal (SIGINT, SIG_IGN);

    int tuberia[2];
    pipe(tuberia);

    printf("Servidor escuchando en el puerto %d...\n", PUERTO);

    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    while(1){
        // El servidor espera un cliente
        int client_fd = accept(server_fd,(struct sockaddr *)&client_addr, &addr_len);
        if(client_fd < 0) continue;

        pid_t pid = fork(); //Creo el proceso hijo

        if (pid == 0){
            //Dodigo del hijo
            close(server_fd); 
            close(tuberia[0]);

            char *ip_cliente = inet_ntoa (client_addr.sin_addr);
            write(tuberia[1], ip_cliente, strlen (ip_cliente)+1);
            close (tuberia[1]);

            char buffer[100] = {0};
            recv(client_fd, buffer, 100,0);

            Episodio ep;
            char respuesta[256];
            if (buscar_episodio(buffer, &ep)){
                formatear_respuesta(&ep, respuesta);    
            } else {
                sprintf(respuesta, "Error: Episodio '%s' no encontrado. \n", buffer);
            }
            send(client_fd, respuesta,strlen(respuesta), 0);
            close(client_fd);
            exit(0); //El hijo termina
        } else if (pid > 0) {
            // Codigo del padre
            close(client_fd);
            close(tuberia[1]);

            char ip_recibida[50] = {0};
            read(tuberia[0], ip_recibida, sizeof(ip_recibida));

            printf("[Padre Pid %d] Conexion del hijo (PID: %d) desde IP: %s\n", getpid(),pid, ip_recibida);
        }
    }

    return 0;
}