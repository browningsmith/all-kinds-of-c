all: rbt.o rbtprint.o rbtest rbtestprint



./include/doublell.h: ../doublell/doublell.h
	-mkdir include
	cp ../doublell/doublell.h include/

./lib/doublell.o: ../doublell/doublell.o
	-mkdir lib
	cp ../doublell/doublell.o lib/

rbt.c: rbt.h rbtimpl.h

rbt.o: rbt.c
	gcc -Wall -c -o rbt.o rbt.c

rbtest: rbt.o rbtest.o
	gcc -Wall -o rbtest rbt.o rbtest.o

rbtest.c: rbt.h rbtimpl.h

rbtest.o: rbtest.c
	gcc -Wall -c -o rbtest.o rbtest.c

rbtestprint: rbt.o ./lib/doublell.o rbtprint.o rbtestprint.o
	gcc -Wall -o rbtestprint rbt.o lib/doublell.o rbtprint.o rbtestprint.o

rbtestprint.c: rbt.h rbtprint.h rbtprintimpl.h

rbtestprint.o: rbtestprint.c
	gcc -Wall -c -o rbtestprint.o rbtestprint.c

rbtprint.c: rbt.h rbtprint.h rbtprintimpl.h ./include/doublell.h

rbtprint.o: rbtprint.c
	gcc -Wall -c -o rbtprint.o rbtprint.c




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