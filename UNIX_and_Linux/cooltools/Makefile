all: itoa.o cooltests

itoa.o: itoa.c
	gcc -Wall -c -o itoa.o itoa.c

itoa.c: cooltools.h

cooltests: itoa.o cooltests.o
	gcc -Wall -o cooltests itoa.o cooltests.o

cooltests.o: cooltests.c
	gcc -Wall -c -o cooltests.o cooltests.c

cooltests.c: cooltools.h

clean: cleantests cleanitoa

cleantests:
	-rm -rf cooltests cooltests.o

cleanitoa:
	-rm -rf itoa.o

