all: doublell.o dlltest.o dlltest

dlltest: doublell.o dlltest.o
	gcc -Wall -o dlltest doublell.o dlltest.o

dlltest.o: dlltest.c
	gcc -Wall -c -o dlltest.o dlltest.c

doublell.o: doublell.h doublell.c
	gcc -Wall -c -o doublell.o doublell.c

clean: cleandlltest cleandoublell

cleandlltest:
	-rm -rf dlltest.o dlltest

cleandoublell:
	-rm -rf doublell.o

