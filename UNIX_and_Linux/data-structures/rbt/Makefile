all: rbtest rbt.o rbtprint.o

rbtest: rbt.o rbtprint.o rbtest.o
	gcc -Wall -o rbtest rbt.o rbtest.o

rbtest.o: rbtest.c
	gcc -Wall -c -o rbtest.o rbtest.c

rbt.o: rbt.h rbtimpl.h rbt.c
	gcc -Wall -c -o rbt.o rbt.c

rbtprint.o: rbtprint.h rbtprint.c
	gcc -Wall -c -o rbtprint.o rbtprint.c

clean: cleanrbtest cleanrbt cleanrbtprint

cleanrbtest:
	-rm -rf rbtest rbtest.o

cleanrbt:
	-rm -rf rbt.o

cleanrbtprint:
	-rm -rf rbtprint.o
	