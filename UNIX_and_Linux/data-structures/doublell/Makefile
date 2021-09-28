CC = gcc
CFLAGS = -Wall

all: ./lib/doublell.o ./bin/dlltest



./bin:
	mkdir bin

./bin/dlltest: ./lib/doublell.o ./lib/dlltest.o | ./bin
	$(CC) $(CFLAGS) -o $@ $< ./lib/dlltest.o

./include/doublellimpl.h: ./include/doublell.h
	touch $@

./lib:
	mkdir lib

./lib/dlltest.o: ./src/dlltest.c | ./lib
	$(CC) $(CFLAGS) -c -o $@ $<

./lib/doublell.o: ./src/doublell.c | ./lib
	$(CC) $(CFLAGS) -c -o $@ $<

./src/dlltest.c: ./include/doublell.h ./include/doublellimpl.h
	touch $@

./src/doublell.c: ./include/doublell.h ./include/doublellimpl.h
	touch $@


clean:
	rm ./bin/* ./lib/*
