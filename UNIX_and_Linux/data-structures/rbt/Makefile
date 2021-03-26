all: rbtest

rbtest: rbt.o rbtprinter.o rbtest.o
	gcc -Wall -o rbtest rbt.o rbtprinter.o rbtest.o

rbtest.o: rbtest.c
	gcc -Wall -c -o rbtest.o rbtest.c

rbt.o: rbt.h rbt.c
	gcc -Wall -c -o rbt.o rbt.c

rbtprinter.o: rbtprinter.h rbtprinter.c
	gcc -Wall -c -o rbtprinter.o rbtprinter.c

clean: cleanrbtest cleanrbt cleanrbtprinter

cleanrbtest:
	-rm -rf rbtest rbtest.o

cleanrbt:
	-rm -rf rbt.o

cleanrbtprinter:
	-rm -rf rbtprinter.o