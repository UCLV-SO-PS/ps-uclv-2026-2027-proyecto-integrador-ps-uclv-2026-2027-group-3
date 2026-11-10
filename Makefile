CC = gcc
CFLAGS = -Wall -pthread
OBJS = monitor.o
LIBS = libmonitor.a

all: $(LIBS) server client

$(LIBS): $(OBJS)
	ar rcs $(LIBS) $(OBJS)

monitor.o: monitor.c monitor.h
	$(CC) $(CFLAGS) -c monitor.c

server: server.c $(LIBS)
	$(CC) $(CFLAGS) -o server server.c $(LIBS)

client: client.c
	$(CC) $(CFLAGS) -o client client.c

clean:
	rm -f *.o $(LIBS) server client