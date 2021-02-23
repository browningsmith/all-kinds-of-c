all: main

main: main.o
	gcc -std=c99 -Wall -o main main.o

main.o: main.c
	gcc -std=c99 -Wall -c -o main.o main.c

clean: cleanmain
	-rm -rf *.txt

cleanmain:
	-rm -rf main main.o

