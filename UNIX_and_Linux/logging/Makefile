all: lgtest

lgtest: lg.o lgtest.o
	gcc -std=c99 -Wall -o lgtest lg.o lgtest.o

lgtest.o: lgtest.c
	gcc -std=c99 -Wall -c -o lgtest.o lgtest.c

lg.o: lg.h lg.c
	gcc -std=c99 -Wall -c -o lg.o lg.c

clean: cleanlgtest cleanlg

cleanlgtest:
	-rm -rf lgtest lgtest.o

cleanlg:
	-rm -rf lg lg.o

