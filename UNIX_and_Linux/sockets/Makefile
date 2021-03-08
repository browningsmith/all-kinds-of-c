all: server client

server: server.o myitoa.o
	gcc -std=c99 -Wall -o server server.o myitoa.o

server.o: server.c
	gcc -std=c99 -Wall -c -o server.o server.c

client: client.o myitoa.o
	gcc -std=c99 -Wall -o client client.o myitoa.o

client.o: client.c
	gcc -std=c99 -Wall -c -o client.o client.c

myitoa.o: myitoa.h myitoa.c
	gcc -std=c99 -Wall -c -o myitoa.o myitoa.c

clean: cleanserver cleanclient cleanmyitoa

cleanserver:
	-rm -rf server server.o

cleanclient:
	-rm -rf client client.o

cleanmyitoa:
	-rm -rf myitoa.o


