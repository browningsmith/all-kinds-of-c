all: server client

server: server.o
	gcc -std=c99 -Wall -o server server.o

server.o: server.c
	gcc -std=c99 -Wall -c -o server.o server.c

client: client.o
	gcc -std=c99 -Wall -o client client.o

client.o: client.c
	gcc -std=c99 -Wall -c -o client.o client.c

clean: cleanserver cleanclient

cleanserver:
	-rm -rf server server.o

cleanclient:
	-rm -rf client client.o


