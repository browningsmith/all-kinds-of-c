CC = gcc
CFLAGS = -Wall


all: ./lib/rbt.o

./lib/%.o: ./src/%.c | ./lib
	$(CC) $(CFLAGS) -c -o $@ $<

./include/rbtimpl.h: ./include/rbt.h
	touch $@

./lib:
	mkdir lib

./src/rbt.c: ./include/rbt.h ./include/rbtimpl.h
	touch $@


clean:
	rm -f bin/* lib/*