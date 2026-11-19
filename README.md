# Proyecto Final: Servidor Concurrente TCP IMDb - "A Knight of the Seven Kingdoms"

**Asignatura:** Programación de Sistemas
**Integrantes:** Hans Moises Blanco y Cristian Alejandro Garcia

## Descripción
Servidor concurrente TCP desarrollado en C para consultar las calificaciones de la serie. Utiliza `fork` para atender múltiples clientes, tuberías (`pipe`) para el reporte de IPs y señales (`SIGCHLD`, `SIGINT`) para el control de procesos y prevención de zombis.

## Comandos de ejecución
1. Compilar todo el proyecto: `make all`
2. Ejecutar prueba automática (Smoke Test): `./server --test-run`
3. Ejecutar el servidor: `./server`
4. Ejecutar el cliente (en otra terminal): `./client`

## Decisiones de diseño
- **Librería Estática:** Se empaquetó la lógica de la base de datos y formateo en `libmonitor.a`.
- **Concurrencia:** El proceso padre escucha en el puerto 6666 y crea un proceso hijo por cada conexión aceptada.
- **IPC (Tuberías):** El hijo envía la dirección IP del cliente al padre a través de una tubería sin nombre antes de procesar la solicitud.
- **Señales:** El servidor ignora `SIGINT` (Ctrl+C) y maneja `SIGCHLD` con `waitpid` para cosechar a los hijos y evitar procesos zombis.