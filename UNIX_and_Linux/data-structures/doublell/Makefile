all: doublell.o dlltest



dlltest: doublell.o dlltest.o
	gcc -Wall -o dlltest doublell.o dlltest.o

dlltest.c: doublell.h doublellimpl.h
	touch dlltest.c

dlltest.o: dlltest.c
	gcc -Wall -c -o dlltest.o dlltest.c

doublell.c: doublell.h doublellimpl.h
	touch doublell.c

doublell.o: doublell.c
	gcc -Wall -c -o doublell.o doublell.c

doublellimpl.h: doublell.h
	touch doublellimpl.h



clean: cleandoublell cleandlltest

cleandlltest:
	-rm -rf dlltest.o dlltest

cleandoublell:
	-rm -rf doublell.o
