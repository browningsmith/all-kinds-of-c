all: rbtest

rbtest: rbt.o rbtest.o
	gcc -Wall -o rbtest rbt.o rbtest.o

rbtest.o: rbt.h rbtest.c
	gcc -Wall -c -o rbtest.o rbtest.c

rbt.o: rbt.h rbt.c
	gcc -Wall -c -o rbt.o rbt.c

clean: cleanrbtest cleanrbt

cleanrbtest:
	-rm -rf rbtest rbtest.o

cleanrbt:
	-rm -rf rbt.o