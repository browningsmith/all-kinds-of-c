all: server

server: server.o
	gcc -std=c99 -Wall -o server server.o

server.o: server.c
	gcc -std=c99 -Wall -c -o server.o server.c

clean: cleanserver

cleanserver:
	-rm -rf server server.o

