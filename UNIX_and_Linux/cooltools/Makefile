all: itoa.o cooltests


cooltests: itoa.o cooltests.o
	gcc -Wall -o cooltests itoa.o cooltests.o

cooltests.c: cooltools.h
	touch cooltests.c

cooltests.o: cooltests.c
	gcc -Wall -c -o cooltests.o cooltests.c

itoa.c: cooltools.h
	touch itoa.c

itoa.o: itoa.c
	gcc -Wall -c -o itoa.o itoa.c



clean: cleancooltests cleanitoa

cleancooltests:
	-rm -rf cooltests cooltests.o

cleanitoa:
	-rm -rf itoa.o