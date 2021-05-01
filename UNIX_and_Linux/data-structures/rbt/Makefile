all: rbt.o rbtprint.o rbtest rbtestprint



./include/doublell.h: ../doublell/doublell.h
	-mkdir include
	cp ../doublell/doublell.h include/

./lib/doublell.o: ../doublell/doublell.o
	-mkdir lib
	cp ../doublell/doublell.o lib/

rbt.c: rbt.h rbtimpl.h
	touch rbt.c

rbt.o: rbt.c
	gcc -Wall -c -o rbt.o rbt.c

rbtest: rbt.o rbtest.o
	gcc -Wall -o rbtest rbt.o rbtest.o

rbtest.c: rbt.h rbtimpl.h
	touch rbtest.c

rbtest.o: rbtest.c
	gcc -Wall -c -o rbtest.o rbtest.c

rbtestprint: rbt.o ./lib/doublell.o rbtprint.o rbtestprint.o
	gcc -Wall -o rbtestprint rbt.o lib/doublell.o rbtprint.o rbtestprint.o

rbtestprint.c: rbt.h rbtprint.h rbtprintimpl.h
	touch rbtestprint.c

rbtestprint.o: rbtestprint.c
	gcc -Wall -c -o rbtestprint.o rbtestprint.c

rbtimpl.h: rbt.h
	touch rbtimpl.h

rbtprint.c: rbt.h rbtprint.h rbtprintimpl.h ./include/doublell.h
	touch rbtprint.c

rbtprint.h: rbt.h
	touch rbtprint.h

rbtprint.o: rbtprint.c
	gcc -Wall -c -o rbtprint.o rbtprint.c

rbtprintimpl.h: rbtprint.h
	touch rbtprintimpl.h



clean: cleanrbt cleanrbtprint cleanrbtest cleanrbtestprint

cleandoublell:
	-rm -rf lib/doublell.o

cleanrbt:
	-rm -rf rbt.o

cleanrbtest:
	-rm -rf rbtest rbtest.o

cleanrbtestprint:
	-rm -rf rbtestprint rbtestprint.o

cleanrbtprint:
	-rm -rf rbtprint.o