all: rbt.o rbtprint.o rbtest rbtestprint

rbt.o: rbt.c
	gcc -Wall -c -o rbt.o rbt.c

rbt.c: rbt.h rbtimpl.h

rbtprint.o: rbtprint.c
	gcc -Wall -c -o rbtprint.o rbtprint.c

rbtprint.c: rbt.h rbtprint.h rbtprintimpl.h ./include/doublell.h

./include/doublell.h: ../doublell/doublell.h
	-mkdir include
	cp ../doublell/doublell.h include/

rbtest: rbt.o rbtest.o
	gcc -Wall -o rbtest rbt.o rbtest.o

rbtest.o: rbtest.c
	gcc -Wall -c -o rbtest.o rbtest.c

rbtest.c: rbt.h rbtimpl.h

rbtestprint: rbt.o lib/doublell.o rbtprint.o rbtestprint.o
	gcc -Wall -o rbtestprint rbt.o lib/doublell.o rbtprint.o rbtestprint.o

lib/doublell.o: ../doublell/doublell.o
	-mkdir lib
	cp ../doublell/doublell.o lib/

rbtestprint.o: rbtestprint.c
	gcc -Wall -c -o rbtestprint.o rbtestprint.c

rbtestprint.c: rbt.h rbtprint.h rbtprintimpl.h

clean: cleanrbt cleanrbtprint cleanrbtest cleanrbtestprint

cleanrbt:
	-rm -rf rbt.o

cleanrbtprint:
	-rm -rf rbtprint.o

cleanrbtest:
	-rm -rf rbtest rbtest.o

cleanrbtestprint:
	-rm -rf rbtestprint rbtestprint.o

cleandoublell:
	-rm -rf lib/doublell.o