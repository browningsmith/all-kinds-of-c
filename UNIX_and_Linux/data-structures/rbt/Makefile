CC = gcc
CFLAGS = -Wall

all: ./lib/rbt.o


./include/rbtimpl.h: ./include/rbt.h
	touch $@

./lib:
	mkdir lib

./lib/rbt.o: ./src/rbt.c | ./lib
	$(CC) $(CFLAGS) -c -o $@ $<

./src/rbt.c: ./include/rbt.h ./include/rbtimpl.h | ./lib
	touch $@


clean:
	rm bin/* lib/*