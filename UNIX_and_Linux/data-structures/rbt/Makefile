CC := gcc
CFLAGS := -Wall

all: rbt.o rbtprint.o rbtest rbtestprint rbtplayer



./include/cooltools.h: ../../cooltools/cooltools.h
	-mkdir include
	cp ../../cooltools/cooltools.h include/

./include/doublell.h: ../doublell/doublell.h
	-mkdir include
	cp ../doublell/doublell.h include/

./lib/doublell.o: ../doublell/doublell.o
	-mkdir lib
	cp ../doublell/doublell.o lib/

./lib/itoa.o: ../../cooltools/itoa.o
	-mkdir lib
	cp ../../cooltools/itoa.o lib/

rbt.c: rbt.h rbtimpl.h
	touch rbt.c

rbt.o: rbt.c
	$(CC) $(CFLAGS) -c -o rbt.o rbt.c

rbtest: rbt.o rbtest.o ./lib/doublell.o ./lib/itoa.o rbtprint.o
	$(CC) $(CFLAGS) -o rbtest rbt.o rbtest.o lib/doublell.o lib/itoa.o rbtprint.o

rbtest.c: rbt.h rbtimpl.h rbtprint.h ./include/cooltools.h
	touch rbtest.c

rbtest.o: rbtest.c
	$(CC) $(CFLAGS) -c -o rbtest.o rbtest.c

rbtestprint: rbt.o ./lib/doublell.o ./lib/itoa.o rbtprint.o rbtestprint.o
	$(CC) $(CFLAGS) -o rbtestprint rbt.o lib/doublell.o lib/itoa.o rbtprint.o rbtestprint.o

rbtestprint.c: rbt.h rbtprint.h rbtprintimpl.h ./include/cooltools.h
	touch rbtestprint.c

rbtestprint.o: rbtestprint.c
	$(CC) $(CFLAGS) -c -o rbtestprint.o rbtestprint.c

rbtimpl.h: rbt.h
	touch rbtimpl.h

rbtplayer: rbt.o ./lib/doublell.o ./lib/itoa.o rbtprint.o rbtplayer.o
	$(CC) $(CFLAGS) -o rbtplayer rbt.o lib/doublell.o lib/itoa.o rbtprint.o rbtplayer.o

rbtplayer.o: rbtplayer.c
	$(CC) $(CFLAGS) -c -o rbtplayer.o rbtplayer.c

rbtplayer.c: ./include/cooltools.h rbt.h rbtprint.h
	touch rbtplayer.c

rbtprint.c: rbt.h rbtprint.h rbtprintimpl.h ./include/doublell.h
	touch rbtprint.c

rbtprint.h: rbt.h
	touch rbtprint.h

rbtprint.o: rbtprint.c
	$(CC) $(CFLAGS) -c -o rbtprint.o rbtprint.c

rbtprintimpl.h: rbtprint.h ./include/doublell.h
	touch rbtprintimpl.h



clean: cleanrbt cleanrbtprint cleanrbtest cleanrbtestprint cleanrbtplayer

cleandoublell:
	-rm -rf lib/doublell.o

cleanitoa:
	-rm -rf lib/itoa.o

cleanrbt:
	-rm -rf rbt.o

cleanrbtest:
	-rm -rf rbtest rbtest.o

cleanrbtestprint:
	-rm -rf rbtestprint rbtestprint.o

cleanrbtprint:
	-rm -rf rbtprint.o

cleanrbtplayer:
	-rm -rf rbtplayer rbtplayer.o