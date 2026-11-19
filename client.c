#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PUERTO 6666
#define IP_SERVIDOR "127.0.0.1"

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) { perror("Error socket"); return 1; }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PUERTO);
    inet_pton(AF_INET, IP_SERVIDOR, &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("Error de conexion"); return 1;
    }

    char codigo[10];
    char buffer[256] = {0};

    printf("Conectado al servidor IMDb.\n");
    printf("Ingrese el codigo del episodio (ej. S01E01): ");
    scanf("%s", codigo);

    send(sock, codigo, strlen(codigo) + 1, 0);

    recv(sock, buffer, sizeof(buffer), 0);
    printf("\nRespuesta del servidor:\n%s\n", buffer);

    close(sock);
    return 0;
}
