CC = gcc
CFLAGS = -Wall


all: ./lib/rbt.o ./lib/rbtprint.o ./bin/rbtest



./bin:
	mkdir bin

./bin/rbtest: ./lib/rbtest.o ./lib/rbt.o ./lib/itoa.o ./lib/rbtprint.o ./lib/doublell.o | ./bin
	$(CC) $(CFLAGS) -o $@ ./lib/rbtest.o ./lib/rbt.o ./lib/itoa.o ./lib/rbtprint.o ./lib/doublell.o

./include/cooltools.h: ../../cooltools/include/cooltools.h
	cp $< include/

./include/doublell.h: ../doublell/include/doublell.h
	cp $< include/

./include/rbtimpl.h: ./include/rbt.h
	touch $@

./include/rbtprint.h: ./include/rbt.h
	touch $@

./include/rbtprintimpl.h: ./include/rbtprint.h ../doublell/include/doublell.h
	touch $@

./lib:
	mkdir lib

./lib/doublell.o: ../doublell/src/doublell.c | ./lib
	$(CC) $(CFLAGS) -c -o $@ $<

./lib/itoa.o: ../../cooltools/src/itoa.c | ./lib
	$(CC) $(CFLAGS) -c -o $@ $<

./lib/rbt.o: ./src/rbt.c | ./lib
	$(CC) $(CFLAGS) -c -o $@ $<

./lib/rbtest.o: ./src/rbtest.c | ./lib
	$(CC) $(CFLAGS) -c -o $@ $<

./lib/rbtprint.o: ./src/rbtprint.c | ./lib
	$(CC) $(CFLAGS) -c -o $@ $<

./src/rbt.c: ./include/rbt.h ./include/rbtimpl.h
	touch $@

./src/rbtest.c: ./include/rbt.h ./include/cooltools.h ../../cooltools/include/cooltools.h ./include/rbtimpl.h ./include/rbtprint.h
	touch $@

./src/rbtprint.c: ./include/rbtprint.h ./include/doublell.h ../doublell/include/doublell.h ./include/rbt.h ./include/rbtprintimpl.h
	touch $@

../doublell/include/doublellimpl.h: ../doublell/include/doublell.h
	touch $@

../doublell/src/doublell.c: ../doublell/include/doublell.h ../doublell/include/doublellimpl.h
	touch $@

../../cooltools/src/itoa.c: ../../cooltools/include/cooltools.h
	touch $@



clean:
	rm -f bin/* lib/*