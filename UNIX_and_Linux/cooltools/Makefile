CC = gcc
CFLAGS = -Wall
OBJS = ./lib/itoa.o

all: ./bin/cooltests $(OBJS)



./bin:
	mkdir bin

./bin/cooltests: ./lib/cooltests.o ./lib/itoa.o | ./bin
	$(CC) $(CFLAGS) -o $@ $< ./lib/itoa.o

./lib:
	mkdir lib

./lib/cooltests.o: ./src/cooltests.c | ./lib
	$(CC) $(CFLAGS) -c -o $@ $<

./lib/itoa.o: ./src/itoa.c | ./lib
	$(CC) $(CFLAGS) -c -o $@ $<

./src/cooltests.c: ./include/cooltools.h
	touch $@

./src/itoa.c: ./include/cooltools.h
	touch $@


clean:
	rm lib/* bin/*