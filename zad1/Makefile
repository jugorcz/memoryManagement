CC=gcc
ARCH=ar
CFLAGS= -Wall -ansi #-pedantic
DEPS=Library.h
OBJ= Library.o plik.o
SRC= Library.c plik.c

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

all: library.a library.so clean

library.a: $(OBJ)
	$(ARCH) rsc $@ $^ 

library.so: library_shr.o
	$(CC) -shared -fPIC $< -o $@

library_shr.o: $(SRC)
	$(CC) -fPIC -c $< -o $@

clean:
	rm -f *.o

cleanAll:
	rm -f *.o
	rm -f *.a
	rm -f *.so
