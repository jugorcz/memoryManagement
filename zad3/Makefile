CC=gcc
CFLAGS=-std=c99 
OPT= -Os
DEP=../zad1/Library.h

INCLUDE= -I../zad1

LIB_SHR=-L../zad1/

LIB_STK=../zad1/library.a


all: test_static test_shared clean run

test_static: test_static.o
	$(CC) -o $@ $< $(LIB_STK) $(CFLAGS) $(OPT)
	
test_static.o: test.c $(DEP)
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDE) $(OPT)

test_shared: test_shared.o
	$(CC) -o $@ $< $(LIB_SHR) -lrary $(CFLAGS) -Wl,-rpath=../zad1/ $(OPT)

test_shared.o: test.c $(DEP)
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDE) $(OPT)

clean:
	rm -f *.o

cleanAll:
	rm -f *.o
	rm -f test_shared
	rm -f test_static

run: MOCK_DATA.txt
	printf "OPTIMALIZATION $(OPT)\n..................\n" >> results3.txt
	printf ">>>>>>>>>> test_static <<<<<<<<<\n..................\n" >> results3.txt
	./test_static 100 5 >> results3.txt
	printf "\n\n>>>>>>>>>>test_shared <<<<<<<<<\n..................\n" >> results3.txt
	./test_shared 100 5 >> results3.txt

