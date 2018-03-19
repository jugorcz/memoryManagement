CC=gcc
CFLAGS=-std=c99 -g
DEPS=../zad1/Library.h
INCLUDE=-I../zad1
LIB=../zad1/library.so

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

all: test clean

test: test.o $(LIB)
	$(CC) $(CFLAGS) -o $@ $^ 

clean:
	rm -f *.o
	
cleanAll:
	rm -f *.o
	rm -f test
