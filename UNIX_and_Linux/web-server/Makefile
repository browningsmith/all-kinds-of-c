all: webserver



webserver: webserver.o
	gcc -Wall -o webserver webserver.o

webserver.o: webserver.c
	gcc -Wall -c -o webserver.o webserver.c



clean: cleanwebserver
	-rm -rf webserver webserver.o