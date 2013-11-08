CC=gcc
LFLAGS=-fPIC -c
CFLAGS=-O2 -Wall
prefix=/usr/local

all:
	$(CC) -o cpress.o $(LFLAGS) $(CFLAGS) cpress.c
	$(CC) -o cpress.so -shared cpress.o

example:
	$(CC) -o example $(CFLAGS) main.c

clean:
	rm -rf *o main