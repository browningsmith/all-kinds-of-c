all: cooltests itoa.o

cooltests: cooltests.o itoa.o
	gcc -Wall -o cooltests itoa.o cooltests.o

cooltests.c: cooltools.h

cooltests.o: cooltests.c
	gcc -Wall -c -o cooltests.o cooltests.c

itoa.c: cooltools.h

itoa.o: itoa.c
	gcc -Wall -c -o itoa.o itoa.c

clean: cleantests cleanitoa

cleantests:
	-rm -rf cooltests cooltests.o

cleanitoa:
	-rm -rf itoa.o

